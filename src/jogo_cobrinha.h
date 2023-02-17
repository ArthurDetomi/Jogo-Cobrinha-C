typedef struct{
    int x;
    int y;
}SEGMENTOS;
typedef struct{
    SEGMENTOS segmentos[300];
    char ultima_tecla;
    int tamanho_cobra;
    int tamanho_segmentos;
}COBRA;
typedef struct{
    int x;
    int y;
    int comeu_fruta;
}FRUTA;
typedef struct{
    char apelido[50];
    int pontuacao;
    int velocidade_jogo;
    char ultima_tecla;
    char tecla_2;
    char acao;
}JOGADOR;
typedef struct{
    int qtd_jogadores;
    JOGADOR jogadores[5];
}RANKING;
FRUTA* cria_fruta();
void destroi_fruta(FRUTA *fruta);
JOGADOR* cria_jogador();
void destroi_jogador(JOGADOR *jogador);
void gerar_posicoes_fruta(FRUTA* fruta);
void desenha_fruta(FRUTA* fruta, JOGADOR *jogador, int *tempo);
COBRA* cria_cobra(int tamanho_inicial, int tamanho_segmento);
void destroi_cobra(COBRA *cobra);
RANKING* cria_ranking();
void destroi_ranking(RANKING *ranking);
void desenha_cobra(COBRA *cobra);
void movimenta_cobra(COBRA *cobra);
void aumenta_cobra(COBRA *cobra, FRUTA *fruta);
void verifica_se_perdeu(COBRA *cobra, bool *perdeu);
void verifica_tecla_pressionada(COBRA * cobra);
void desenha_velocidades();
void desenha_menu();
void controles_menu(JOGADOR *jogador);
void acoes_menu(JOGADOR *jogador);
void controle_menu_velocidade(JOGADOR *jogador);
void le_score(RANKING *ranking);
void escreve_score(JOGADOR *jogador);
void desenha_ranking(RANKING *ranking, JOGADOR *jogador);
void desenha_pontuacao(JOGADOR *jogador);
void cor_de_fundo();
void jogar_jogo_padrao();
