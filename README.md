**Documentação do trabalho prático 1**

**Algoritmo e Estrutura de Dados 1**

**Acadêmico:** Geraldo Arthur Detomi

**Professor:** Elverton Carvalho Fazzion


**Movimentação da cobra**

`	`A solução, para movimentar a cobra, primeiramente foi criar uma *struct* de segmentos com coordenadas x e y, como a interface gráfica trabalha, e como a função desenha\_retangulo() da biblioteca funciona.

`	`Logo após, criei uma *struct* cobra contendo ultima\_tecla do tipo *caracter* para saber a última tecla pressionada do usuário; uma variável inteira chamada tamanho\_cobra onde nela armazeno a quantidade de segmentos preenchidos da cobra atual; um vetor da *struct* segmentos de tamanho máximo 300, para preencher cada segmento novo e uma variável inteira chamada tamanho\_segmentos para saber qual o tamanho de cada segmento da cobra.

`	`A solução, basicamente, foi criar uma função para desenhar a cobra e outra para ir preenchendo os segmentos, aumentando a cobra caso ela comesse alguma fruta.

`	`A lógica para o movimento da cobra foi a seguinte: a cada movimento realizado pelo usuário o último segmento do vetor passa a ser a cabeça da cobra (posição 0), e a cabeça da cobra passa a ser o último segmento, porém deslocado seja para direita ou esquerda, para cima ou para baixo na posição x ou y atual. Assim, foi somada a posição atual de cada segmento mais a variável tamanho\_segmento, e logo após, trás todos os outros segmentos para mais perto, numa distância tamanho\_segmentos mais posição x ou y.



**Verificação de colisões da cobra**

`	`A solução para verificar se a cobra colidiu com as paredes foi receber as coordenadas da cabeça da cobra x e y, no caso o segmento da posição 0. Logo após, usando algumas variáveis já pronta da biblioteca como altura\_janela, e largura\_janela e sabendo como funciona o eixo x e y da interface gráfica, determinei os limite superiores, inferiores e laterais.

`	`A seguir, bastou comparar as posições fazendo uma validação com um *if()* perguntando se a posição da cabeça da cobra se encontrava entre esses limites. Para saber se a cobra mordeu o próprio corpo fiz um laço *for()* percorrendo todos os segmentos e comparei com a cabeça, desse modo, caso a cabeça se encontrasse na mesma posição com alguns dos outros segmentos significa que havia perdido: fiz uma verificação de trás pra frente comparando a cabeça com o rabo até o penúltimo segmento.

`	`Para verificar se a cobra comeu a maça utilizei a mesma lógica de coordenadas, fiz cálculos para descobrir a abrangência da área da maçã desenhada, caso a cabeça da cobra passe por essa área significa que a cobra comeu a maçã.











**Função:**

**jogar\_jogo\_padrão();** basta chamar essa função na *main* do programa C e incluir as dependências para jogar um jogo padrão feito por mim.

![](Aspose.Words.a4184637-4889-4c9e-b16a-591e21d0fd20.001.png)












**Tela Inicial do jogo**

`	`Para selecionar jogar basta apertar a tecla “enter”, para sair do jogo basta pressionar a tecla “esc”.

`	`![](Aspose.Words.a4184637-4889-4c9e-b16a-591e21d0fd20.002.png)














**Menu de velocidades**

`	`Para escolher a velocidade basta pressionar a tecla “espaço”, para sair do jogo basta pressionar a tecla “esc”.

![](Aspose.Words.a4184637-4889-4c9e-b16a-591e21d0fd20.003.png)












**Durante o jogo**

`	`Para movimentar a cobra é possível usar as setas do teclado ou as teclas w, a, s,d, para sair do jogo basta pressionar a tecla “esc”, ao sair seu score é salvo.

`		`![](Aspose.Words.a4184637-4889-4c9e-b16a-591e21d0fd20.004.png)













**Perdeu o jogo**

`	`Ao perder o jogo, é listado o ranking mostrando do maior ranking ao menor, caso você aperte a tecla “espaço”, o jogo é reiniciado e você tem uma nova partida, porém a sua pontuação antiga é perdida, essa informação é passada pelo próprio jogo quando se perde a partida.

`		`![](Aspose.Words.a4184637-4889-4c9e-b16a-591e21d0fd20.005.png)![](Aspose.Words.a4184637-4889-4c9e-b16a-591e21d0fd20.006.png)
















