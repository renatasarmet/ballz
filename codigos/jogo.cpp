#include "jogo.h"
//Linha referente para remover o cmd no windows.
//#include <windows.h>

jogo::GameState jogo::estado_jogo = Inicializado;
sf::RenderWindow jogo::janela;
sf::Text jogo::nivelText;
sf::Text jogo::pokebolaText;
sf::Sprite jogo::background;
sf::Music jogo::musica_jogo;
sf::Music jogo::musica_menu;
sf::Music jogo::musica_instrucoes;
bool pokeball::lancado = false;
braco::estado_braco braco::_estado_braco = Rotacionando;
double pokeball::dir = 0;
pokeball jogo::pokebola;
bool pokeball::colidiuOvo = false;
int jogo::rodadaAtual = 0;
bool pokeball::novaRodada = false;
sf::Text Nodetype::valorText;
int pokeball::qtdRestantePokebola = 1;
int pokeball::qtdPokebola = 1;
bool pokeball::colidiuEmCimaOuBaixoOvo = false;
int jogo::entrou_jogando = 0;

void jogo::Start(Plano* plano, braco* hook)
{
    sf::Texture imagem;
    imagem.loadFromFile("imagens/fundo.jpg");
    background.setTexture(imagem); //DEFINE O BACKGROUND
    
    //Resetando as listas
    plano->DeletaTudo();
    
    //Resetando rodada atual e quantidade de pokeball
    rodadaAtual = 1;
    pokebola.reiniciaQtdPokebola();
    pokebola.reiniciaRestante();
    
    //SETANDO OS TEXTOS
    nivelText.setString(to_string(rodadaAtual));
    pokebolaText.setString(to_string(pokebola.get_qtdRestantePokebola()));
    
    //Resetando o Perdeu
    plano->reseta_perdeu_false();
    
    //Setando pokeball para nao lancado
    pokeball::lancado = false;

    // Inicializando o plano
    plano->InsereNplano(rodadaAtual);

    while (!IsExiting())
    {
        loop_jogo(plano, hook);
    }
    
    janela.close();
}

void jogo::CriandoTudo()
{
	janela.create(sf::VideoMode(450, 600), "PokeBallz", sf::Style::Close); //DEFINE TAMANHO DA JANELA, O QUE APARECE NO CABECALHO E FUNCOES DISPONIVEIS (FECHAR, RESIZE, MINIMIZAR)
   
    Plano plano;
	braco hook;

	//LOADANDO AS MUSICAS
	musica_jogo.setLoop(true);
	musica_jogo.openFromFile("sons/pokemon.ogg");
	musica_instrucoes.setLoop(true);
	musica_instrucoes.openFromFile("sons/pokemon1.ogg");
	musica_menu.setLoop(true);
	musica_menu.openFromFile("sons/pokemon2.ogg");

    //LOAD FONT E SETA
    sf::Font fonte;
    fonte.loadFromFile("imagens/pokemon1.ttf");
    
    //SETANDO OS TEXTOS
    nivelText.setFont(fonte);
    nivelText.setPosition(125, 8);
    nivelText.setCharacterSize(22);
    nivelText.setFillColor(sf::Color::White);
    
    pokebolaText.setFont(fonte);
    pokebolaText.setPosition(40, 8);
    pokebolaText.setCharacterSize(22);
    pokebolaText.setFillColor(sf::Color::White);
   
	estado_jogo = jogo::Mostrando_Tela_Inicial;
    jogo::Start(&plano, &hook);

	srand(time(NULL));
}


void jogo::JogarNovamente(Plano* plano, braco* hook)
{
	jogo::Start(plano, hook);
	entrou_jogando = 1;
    estado_jogo = jogo::Jogando;
}
                                    
bool jogo::IsExiting()
{
    if (estado_jogo == jogo::Saindo)
        return true;
    else
        return false;
}

void jogo::loop_jogo( Plano* plano, braco* hook)
{
    switch (estado_jogo)
    {
        case jogo::Mostrando_Menu:
        {
            mostrar_menu();
            break;
        }
        case jogo::Mostrando_Tela_Inicial:
        {
            mostrar_tela_inicial();
            break;
        }
        case jogo::Mostrando_Instrucao:
        {
            mostrar_instrucao();
            break;
        }
        case jogo::Perdendo:
        {
            mostrar_perdeu(plano, hook);
            break;
        }
        case jogo::Jogando:
        {
            sf::Event evento_atual;
            sf::Sprite botao_pausar;
			sf::Texture imagem1;
			
			if (entrou_jogando == 1)
			{
				entrou_jogando = 2;
				musica_jogo.play();
			}

            imagem1.loadFromFile("imagens/pausar.png");
            botao_pausar.setTexture(imagem1);
            botao_pausar.setPosition(335, 3);

            verifica_colisao(plano, hook);
            
            if(pokeball::novaRodada ){
                rodadaAtual += 1;
                pokeball::novaRodada = false;
                plano->InsereNplano(rodadaAtual);
            }
            else if((plano->QuantidadeElementos() == 0) && pokeball::lancado == false ){
                pokebola.reiniciaRestante();
                rodadaAtual += 1;
                plano->InsereNplano(rodadaAtual);
            }
            
            if(plano->get_perdeu())
                estado_jogo = jogo::Perdendo;

            //SETANDO OS TEXTOS
            nivelText.setString(to_string(rodadaAtual));
            pokebolaText.setString(to_string(pokebola.get_qtdRestantePokebola()));
            
            janela.clear();
            janela.draw(background);
            hook->desenhar(janela);
            hook->update_todos();
			pokebola.desenhar(janela);
            plano->desenha_todos_plano(janela);
            janela.draw(nivelText);
            janela.draw(pokebolaText);
            janela.draw(botao_pausar);
			janela.display();
            
            while (janela.pollEvent(evento_atual))
            {
                switch (evento_atual.type)
                {
                    case sf::Event::Closed:
                        estado_jogo = jogo::Saindo;
                        break;
                    case sf::Event::KeyPressed:
						if (evento_atual.key.code == sf::Keyboard::Escape)
						{
							musica_jogo.pause();
							estado_jogo = jogo::Mostrando_Menu;
						}
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (evento_atual.mouseButton.button == sf::Mouse::Left && pokeball::lancado == false)
                        {
                            if (botao_pausar.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y))
                            {                                
								musica_jogo.pause();
								estado_jogo = jogo::Mostrando_Menu;
                            }

							else{
								braco::_estado_braco = braco::Pokebola_Lancada;
								pokeball::dir = (hook->get_rotacao() + 90)*0.0174532925;
							}
                        }
						break;
						
                    default:
                        break;
                }
            }
            break;
        }
    }
}

void jogo::mostrar_tela_inicial()
{
    Tela_Inicial tela_incial;

	estado_jogo = jogo::Mostrando_Menu;

    tela_incial.Mostrar(janela);
}

void jogo::mostrar_perdeu(Plano* plano, braco* hook)
{
    Perdeu perdeu;
    Perdeu::perdeu resultado = perdeu.Mostrar(janela, rodadaAtual);
    switch (resultado)
    {
        case Perdeu::Sair:
            estado_jogo = jogo::Saindo;
            break;
        case Perdeu::Jogar_Novamente:
			entrou_jogando = 1;
            estado_jogo = jogo::Jogando;
            jogo::JogarNovamente(plano, hook);
            break;
    }
}

void jogo::verifica_colisao( Plano* plano, braco* hook)
{
    Nodetype *Paux;
    bool ok = false;
    Paux = plano->PegaElementoN(1);
    
    while ((Paux != NULL) && (ok == false))
    {
        if (Paux->colidiu(hook->_pokeball))
        {
            pokeball::colidiuOvo = true;
            braco::_estado_braco = braco::Acertou;
            if(Paux->get_valor()>1){
                Paux->set_valor(Paux->get_valor()-1);
            }
            else{
                if (Paux->get_valor() == -1){
                    pokebola.aumentaQtdPokebola();
                    pokeball::colidiuOvo = false;
                    pokeball::colidiuEmCimaOuBaixoOvo = false;
                }
                plano->ProcuraRemove(Paux->get_id(), ok);
            }
            
        }
        Paux = Paux->get_next();
    }
}

void jogo::mostrar_menu()
{
    Menu menu;

	musica_menu.play();

    Menu::menu_inicial resultado = menu.Mostrar(janela);

    switch (resultado)
    {
        case Menu::Sair:
            estado_jogo = jogo::Saindo;
            break;
        case Menu::Jogar:
			entrou_jogando = 1;
			musica_menu.pause();
            estado_jogo = jogo::Jogando;
            break;
        case Menu::Instrucoes:
			musica_menu.pause();
            estado_jogo = jogo::Mostrando_Instrucao;
            break;
    }
}
                       
void jogo::mostrar_instrucao()
{
    Instrucoes instrucao;
	
	musica_instrucoes.play();

    instrucao.set_k(1);
    int continua = 1;
    while (continua == 1) {
        Instrucoes::instrucoes_opcoes resultado = instrucao.Mostrar(janela);
        switch (resultado)
        {
            case Instrucoes::Menu:
				musica_instrucoes.pause();
                estado_jogo = jogo::Mostrando_Menu;
                continua = 0;
                break;
            case Instrucoes::Jogar:
				entrou_jogando = 1;
				musica_instrucoes.pause();
                estado_jogo = jogo::Jogando;
                continua = 0;
                break;
            case Instrucoes::Sair:
                estado_jogo = jogo::Saindo;
                continua = 0;
                break;
            case Instrucoes::Proximo:
                instrucao.proximo_k();
                break;
            case Instrucoes::Anterior:
                instrucao.anterior_k();
                break;
        }
    }
}

int main(int argc, char** argv)
{
	//Linhas referentes para remover o cmd no windows.
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow( hWnd, SW_HIDE );
    jogo::CriandoTudo();
    
    return 0;
}