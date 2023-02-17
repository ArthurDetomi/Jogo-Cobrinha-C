# jogo-aeds-1 - Repositório base para o TP de AEDS 1 / 2022.2

## Sobre este repositório

Para começar a desenvolver o seu trabalho, clone este repositório. Ele vem com
todas as configurações de debug e compilação para Windows e para Linux
configuradas e testadas, para que você possa focar em desenvolver o jogo.

## Como usar?

Primeiro, certifique-se de instalar **Git**. Os comandos para instalar estão
disponíveis abaixo, dependendo do seu Sistema Operacional.

<details>
<summary><b>🐧 Para Debian/Ubuntu/Pop_OS!/ElementaryOS</b></summary>

```sh
$ sudo apt install git
```

</details>

<details>
<summary><b>🐧 Para ArchLinux</b></summary>

```sh
$ sudo pacman -S git
```

</details>

<details>
<summary><b>🪟 Para Windows</b></summary>

Para Windows 10 (acima da versão 1809) e Windows 11, rode o seguinte comando no
seu PowerShell:

```pwsh
PS> winget install Git.Git
```

Para versões do Windows mais antigas (10 < 1809, 8.1, 8, 7, Vista, XP, Etc.),
[baixe o instalador aqui](https://git-scm.com/download/win).

**⚠️ Importante**: Após instalar o Git, feche e abra a linha de comando que você
usou

</details>

<br/>

Com o **Git** instalado, escolha uma pasta qualquer no seu computador, entre
nela com o seu terminal e rode os seguintes comandos para clonar este
repositório:

```sh
$ git clone --recursive https://github.com/syndelis/jogo-aeds-1 tp-aeds1
$ cd tp-aeds1
```

Esse comando criará uma pasta chamada **`tp-aeds1`** com todo o conteúdo deste
repositório. A partir daí, basta alterar os arquivos dentro de **`src/`** para
desenvolver o seu jogo!

## Compilando o seu jogo

Primeiro, instale as dependências [detalhadas aqui](https://github.com/Syndelis/jogo.h#instalando-as-depend%C3%AAncias-).

Após instaladas, rode o comando de compilação, dependendo do seu Sistema
Operacional:

<details>
<summary><b>🐧 Para Linux</b></summary>

```sh
$ make
```

</details>

<details>
<summary><b>🪟 Para Windows</b></summary>

```pwsh
PS> .\compilar.ps1
```

**⚠️ Atenção**: Pode ser que o comando acima falhe porque "a execução de
scripts foi desabilitada neste sistema". Caso ocorra com você, abra um
PowerShell como administrador e rode o seguinte comando
**e reinicie seu computador**:

```pwsh
PS> Set-ExecutionPolicy Unrestricted
```

</details>

## Documentação

A documentação detalhando como usar a biblioteca de desenvolvimento de jogos
**`jogo.h`** [está disponível aqui](https://syndelis.github.io/jogo.h).

## Dúvidas

**Alunos da disciplina**: Se tiverem qualquer dúvida, contatem a mim (Brenno) ou
ao professor.

**Não alunos**: Abra uma *Issue* no [repositório da bibliotca](https://github.com/syndelis/jogo.h).