#include <jogo.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "jogo_cobrinha.h"

FRUTA* cria_fruta(){
    FRUTA *fruta = (FRUTA*) malloc(sizeof(FRUTA));
    fruta->comeu_fruta = 1;
    return fruta;
}

void destroi_fruta(FRUTA *fruta){
    free(fruta);
}

JOGADOR* cria_jogador(){
    JOGADOR *jogador = (JOGADOR*) malloc(sizeof(JOGADOR));
    jogador->pontuacao = -1;
    jogador->acao = 'j';
    jogador->velocidade_jogo = 10;
    return jogador;
}

void destroi_jogador(JOGADOR *jogador){
    free(jogador);
}

void gerar_posicoes_fruta(FRUTA* fruta){
    //limites
    int tamanho_espaco = 280;
    int limite_inferior = altura_janela - tamanho_espaco;
    int limite_lateral = largura_janela - tamanho_espaco;
    //gerando posição para y
    fruta->y = (rand() % limite_inferior) + 100;
    fruta->x = (rand() % limite_lateral) + 100;
}

void desenha_fruta(FRUTA* fruta, JOGADOR *jogador, int *tempo){
    if(fruta->comeu_fruta || *tempo == 402){
        gerar_posicoes_fruta(fruta);
        if(fruta->comeu_fruta){
            *tempo = 0;
            jogador->pontuacao++;
        }
        fruta->comeu_fruta = 0;
    }
    cor(VERMELHO);
    desenha_circulo(fruta->x, fruta->y , 6);
}

COBRA* cria_cobra(int tamanho_inicial, int tamanho_segmento){
    COBRA *cobra = (COBRA*) malloc(sizeof(COBRA));
    cobra->tamanho_cobra = tamanho_inicial;
    cobra->ultima_tecla = 'd';
    cobra->tamanho_segmentos = tamanho_segmento;
    int posicao_inicial = largura_janela / 2;
    for(int i = 0; i < cobra->tamanho_cobra; i++){
        cobra->segmentos[i].x = posicao_inicial * (i+1);
        cobra->segmentos[i].y = posicao_inicial * (i+1);
    }
    return cobra;
}

void destroi_cobra(COBRA *cobra){
    free(cobra);
}

RANKING* cria_ranking(){
    RANKING *ranking = (RANKING*) malloc(sizeof(RANKING));
    return ranking;
}

void destroi_ranking(RANKING *ranking){
    free(ranking);
}

void desenha_cobra(COBRA *cobra){
    for(int i = 0; i < cobra->tamanho_cobra; i++){
        cor(PRETO);
        desenha_retangulo(
            cobra->segmentos[i].x,
            cobra->segmentos[i].y,
            cobra->tamanho_segmentos,
            cobra->tamanho_segmentos
        );
    }
}

void movimenta_cobra(COBRA *cobra){
    SEGMENTOS segmento_aux;
    segmento_aux.x = cobra->segmentos[0].x;
    segmento_aux.y = cobra->segmentos[0].y;
    int posicao_ultimo_seg = cobra->tamanho_cobra;
    switch(cobra->ultima_tecla){
        case 'd':
            segmento_aux.x = segmento_aux.x + cobra->tamanho_segmentos;
        break;
        case 'a':
            segmento_aux.x = segmento_aux.x - cobra->tamanho_segmentos;
        break;
        case 'w':
            segmento_aux.y = segmento_aux.y - cobra->tamanho_segmentos;
        break;
        case 's':
            segmento_aux.y = segmento_aux.y + cobra->tamanho_segmentos;
        break;
    }
    for(int i = cobra->tamanho_cobra - 1; i >= 0; i--){
        cobra->segmentos[i + 1] = cobra->segmentos[i];
    }
    cobra->segmentos[0] = segmento_aux;
}

void aumenta_cobra(COBRA *cobra, FRUTA *fruta){
    int posicao_cabeca_atual_x = cobra->segmentos[0].x;
    int posicao_cabeca_atual_y = cobra->segmentos[0].y;
    if(posicao_cabeca_atual_x >= fruta->x - 12 && posicao_cabeca_atual_x <= fruta->x + 12 &&
    posicao_cabeca_atual_y >= fruta->y - 12 && posicao_cabeca_atual_y <= fruta->y + 12){
        para_som("src/musica_tema.mp3");
        recomeca_som("src/comeu.wav");
        int posicao_atual_x = cobra->segmentos[cobra->tamanho_cobra - 1].x;
        int posicao_atual_y = cobra->segmentos[cobra->tamanho_cobra - 1].y;
        cobra->tamanho_cobra++;
        cobra->segmentos[cobra->tamanho_cobra - 1].x = posicao_atual_x + cobra->tamanho_segmentos;
        cobra->segmentos[cobra->tamanho_cobra - 1].y = posicao_atual_y;
        fruta->comeu_fruta = 1;
    }

}  

void verifica_se_perdeu(COBRA *cobra, bool *perdeu){
    //limites
    int limite_superior = 0;
    int limite_inferior = altura_janela - cobra->tamanho_segmentos;
    int posicao_atual_x = cobra->segmentos[0].x;
    int posicao_atual_y = cobra->segmentos[0].y;

    //se encostou nos limites
    if(posicao_atual_y < limite_superior ||
    posicao_atual_y > limite_inferior){
        *perdeu = true;
    }
    if(posicao_atual_x > (largura_janela - cobra->tamanho_segmentos) ||
    posicao_atual_x < 0){
        *perdeu = true;
    }

    //se mordeu o próprio corpo
    if(cobra->tamanho_cobra >= 5){
        for(int i = cobra->tamanho_cobra - 1; i > 0; i--){
            if(posicao_atual_x == cobra->segmentos[i].x && posicao_atual_y == cobra->segmentos[i].y){
                *perdeu = true;
                break;
            } 
        }
    }

}

void verifica_tecla_pressionada(COBRA * cobra){ 
    if(cobra->ultima_tecla != 'w'){
        if( tecla_acabou_de_ser_apertada(BAIXO) || tecla_acabou_de_ser_apertada('S') || tecla_acabou_de_ser_apertada('s') && cobra->ultima_tecla != 'w'){
            cobra->ultima_tecla = 's';
        }
    }
    if(cobra->ultima_tecla != 's'){
        if( tecla_acabou_de_ser_apertada(CIMA) || tecla_acabou_de_ser_apertada('W') || tecla_acabou_de_ser_apertada('w') && cobra->ultima_tecla != 's'){
            cobra->ultima_tecla = 'w';
        }
    }
    if(cobra->ultima_tecla != 'a'){
        if( tecla_acabou_de_ser_apertada(DIREITA) || tecla_acabou_de_ser_apertada('D') || tecla_acabou_de_ser_apertada('d') && cobra->ultima_tecla != 'a'){
            cobra->ultima_tecla = 'd';
        }
    }
    if(cobra->ultima_tecla != 'd'){
        if( tecla_acabou_de_ser_apertada(ESQUERDA) || tecla_acabou_de_ser_apertada('a') || tecla_acabou_de_ser_apertada('A')){
            cobra->ultima_tecla = 'a';
        }
    }
}

void desenha_velocidades(){
    fonte("src/goblin_one.ttf", 16);
    cor(PRETO);
    fonte("src/goblin_one.ttf", 21);
    desenha_texto(largura_janela/2 - 125, altura_janela/2 - 80, "%5s", "Velocidades de jogo");
    fonte("src/goblin_one.ttf", 16);
    desenha_texto(largura_janela/2 - 80, altura_janela/2, "%18s", "Lenta");
    desenha_texto(largura_janela/2 - 80, altura_janela/2 + 80, "%18s", "Normal");
    fonte("src/goblin_one.ttf", 16);
    desenha_texto(largura_janela/2 - 80, altura_janela/2 + 160, "%18s", "Rapida");
    cor(PRETO);
}

void desenha_menu(){
    fonte("src/goblin_one.ttf", 16);
    cor(PRETO);
    fonte("src/goblin_one.ttf", 21);
    desenha_texto(largura_janela/2 - 125, altura_janela/2 - 80, "%5s", "JOGO DA COBRINHA");
    fonte("src/goblin_one.ttf", 16);
    desenha_texto(largura_janela/2 - 80, altura_janela/2, "%18s", "JOGAR");
    cor(AMARELO);
    desenha_texto(largura_janela/2 - 80, altura_janela/2 + 160, "%18s", "By Geraldo Arthur");
    cor(PRETO);
}
 
void controles_menu(JOGADOR *jogador){
    if(tecla_pressionada(ENTER)){
        jogador->ultima_tecla = 'e';
    }
    if(tecla_pressionada(ESPACO)){
        jogador->ultima_tecla = 'j';
    }
    if(tecla_pressionada(ESC)){
        janela_deve_fechar();
    }
}

void acoes_menu(JOGADOR *jogador){
    preenchimento(false);
    if(jogador->acao == 'j' || jogador->acao == 's'){
        jogador->velocidade_jogo = 3;
        desenha_retangulo(
            largura_janela/2 - 100,
            altura_janela/2 - 20,
            200,
            25
        );
    }
    if(jogador->acao == 'n'){
        jogador->velocidade_jogo = 2;
        desenha_retangulo(
            largura_janela/2 - 100,
            altura_janela/2 + 60,
            200,
            25
        );
    }
    if(jogador->acao == 'f'){
        jogador->velocidade_jogo = 1;
        desenha_retangulo(
            largura_janela/2 - 100,
            altura_janela/2 + 140,
            200,
            25
        );
    }
}

void controle_menu_velocidade(JOGADOR *jogador){
   char ultima_acao = jogador->acao; 
   if(ultima_acao != 's' && ultima_acao != 'f' && ultima_acao != 'n'){
        ultima_acao = 'n';
   }
   if(tecla_acabou_de_ser_apertada(ESC)){ 
        janela_deve_fechar(); 
   }
   if(tecla_acabou_de_ser_apertada(BAIXO) || tecla_acabou_de_ser_apertada(ESQUERDA)){
        if(jogador->acao == 's'){
            jogador->acao = 'n';
        }
        if(ultima_acao == 'n'){
            jogador->acao = 'f';
        }
        if(ultima_acao == 'f'){
            jogador->acao = 's';
        }
   }
   if(tecla_acabou_de_ser_apertada(CIMA) || tecla_acabou_de_ser_apertada(DIREITA)){
        if(jogador->acao == 's'){
            jogador->acao = 'f';
        }
        if(ultima_acao == 'n'){
            jogador->acao = 's';
        }
        if(ultima_acao == 'f'){
            jogador->acao = 'n';
        }
   }
   if(tecla_pressionada(ESPACO)){
        jogador->ultima_tecla = 't';   
    }
}


void le_score(RANKING *ranking){
    int MAX_TAM = 100;
    char buf[MAX_TAM];
	int qtd_jogadores = 0;
    bool arq_existe = true;
    JOGADOR jogadores[10];
    

	FILE *arq;
	arq = fopen("src/score.txt", "r");
    if(arq == NULL){
        arq_existe = false;
    }
    if(arq_existe){
        int i = 0;
        fgets(buf, MAX_TAM, arq);
        while(!feof(arq)){

            jogadores[i].pontuacao = atoi(strtok(buf,","));
            strcpy(jogadores[i].apelido, strtok(NULL, ","));
            fgets(buf, MAX_TAM, arq);
            i++;
            qtd_jogadores++;
        
        }
        fclose(arq);
    }
    JOGADOR melhor_jogador = jogadores[0];
    int posicao = 0;
    ranking->qtd_jogadores = (qtd_jogadores >= 5) ? 5: qtd_jogadores;
    for(int i = 0; i < ranking->qtd_jogadores; i++){
        //garantindo que sejam só 5
        if(i == 5){
            break;
        }
        JOGADOR jogador_aux;
        for(int j = i; j < qtd_jogadores; j++){
            if(jogadores[j].pontuacao > melhor_jogador.pontuacao){
                melhor_jogador = jogadores[j];
                posicao = j;
            }
        }
        jogador_aux = jogadores[i];
        jogadores[i] = melhor_jogador; 
        jogadores[posicao] = jogador_aux;
        ranking->jogadores[i] = melhor_jogador;
        melhor_jogador.pontuacao = 0;
    }
    
}


void escreve_score(JOGADOR *jogador){
    FILE* arq;
    arq = fopen("src/score.txt", "a");
    if(arq == NULL){
        arq = fopen("score.txt", "w");
    }
    int result = fprintf(arq,"%d,%s\n", jogador->pontuacao, jogador->apelido);
    if(result < 0){
        printf("Não foi possivel gravar seu score\n");
    }
    fclose(arq);
}

void desenha_ranking(RANKING *ranking, JOGADOR *jogador){
    cor(PRETO);
    fonte("src/goblin_one.ttf", 16);
    desenha_texto(largura_janela/2 - 150, 100 - 80, "%5s", "RANKING DE JOGADORES");
    fonte("src/ubuntu.ttf", 18);
    desenha_texto(largura_janela/2 - 125, 100 - 20, "%5s", "Posicao  Nome Pontuacao");
    cor(VERMELHO);
    fonte("src/ubuntu.ttf", 15);
    desenha_texto(largura_janela/2 - 100, 100,"Sua pontuacao %s = %d", 
        jogador->apelido,
        jogador->pontuacao
    );
    desenha_texto(largura_janela/2 - 150, 120,"Se jogar novamente sera reinicado a pontuacao");
    cor(PRETO);
    fonte("src/ubuntu.ttf", 15);
    int distancia = 0;
    if(ranking->qtd_jogadores > 0){
        for(int i = 0; i < ranking->qtd_jogadores; i++){
            desenha_texto(largura_janela/2 - 110, 140 + distancia, "%10d %10s %10d",
                i+1,
                ranking->jogadores[i].apelido,
                ranking->jogadores[i].pontuacao
            );
            distancia += 80;
        }
    }
}

void desenha_pontuacao(JOGADOR *jogador){
    fonte("src/goblin_one.ttf", 21);
    cor(PRETO);
    desenha_texto(100, 25, "SCORE = %d", jogador->pontuacao);
}

void cor_de_fundo(){
    cor(AZUL_CLARO);
    desenha_retangulo(
        0,
        0,
        largura_janela,
        altura_janela
    );
}

void jogar_jogo_padrao(){
    srand((unsigned)time(NULL));
    COBRA *cobra  = cria_cobra(3, 10);
    FRUTA *fruta = cria_fruta();
    RANKING *ranking = cria_ranking();
    JOGADOR *jogador = cria_jogador();
    le_score(ranking);
    printf("Digite seu apelido no jogo:");
    fgets(jogador->apelido, 50, stdin);  
    jogador->apelido[strlen(jogador->apelido) - 1] = '\0';
    
    abre_janela(640, 480);
    
    char musica_tema[40];
    strcpy(musica_tema, "src/musica_tema.mp3");
    toca_som_em_loop(musica_tema);

    // variaveis para controle de jogo
    int temporizador = 0;
    bool perdeu = false;
    bool menu = true;
    bool menu_velocidades = true;
    bool escreveu_score = false;
    int tempo_gerar_fruta = 0;

    while (janela_esta_aberta()){

        cor_de_fundo();
        if(menu){
            desenha_menu();
            controles_menu(jogador);
            acoes_menu(jogador);
            if(jogador->ultima_tecla != 'e'){
                continue;
            }
            jogador->acao = 's';
            menu = false;
        }
        if(menu_velocidades){
            desenha_velocidades();
            controle_menu_velocidade(jogador);
            acoes_menu(jogador);
            if(jogador->ultima_tecla != 't'){
               continue;
            }
            jogador->ultima_tecla = 's';
            menu_velocidades = false;
        }
        
        // se perdeu o jogo
        verifica_se_perdeu(cobra, &perdeu);
        if(perdeu == true){
            le_score(ranking);
            desenha_ranking(ranking, jogador);
            controles_menu(jogador);
            if(!som_esta_tocando(musica_tema)){
               recomeca_som(musica_tema);
            }
            if(jogador->ultima_tecla != 'j'){
                continue;
            }

            free(cobra);
            free(fruta);
            COBRA *nova_cobra = cria_cobra(3, 10); 
            FRUTA *nova_fruta = cria_fruta();
            cobra = nova_cobra;
            fruta = nova_fruta;
            jogador->pontuacao = -1;
            jogador->ultima_tecla = 'z';
            perdeu = false;
        }

        temporizador = (temporizador + 1) % jogador->velocidade_jogo;
        // apenas para evitar que ultrapasse um valor muito grande 
        if(temporizador > 1000000){
            temporizador = 0;
        }

        
        if(tecla_acabou_de_ser_apertada(ESC)){
            janela_deve_fechar();
        }

        // caso demore muito para pegar a fruta, gera outra posição
        if(tempo_gerar_fruta == 402){
            tempo_gerar_fruta = 0;
        }
        tempo_gerar_fruta++;

        // logica da cobra e frutas
        aumenta_cobra(cobra, fruta); 
        desenha_cobra(cobra);
        if(temporizador == 0){
            movimenta_cobra(cobra);
        }
        desenha_fruta(fruta, jogador, &tempo_gerar_fruta);
        desenha_pontuacao(jogador);
        verifica_tecla_pressionada(cobra);

    }
    fecha_janela();
    escreve_score(jogador);
    destroi_cobra(cobra);
    destroi_jogador(jogador);
    destroi_fruta(fruta);
    destroi_ranking(ranking);
}