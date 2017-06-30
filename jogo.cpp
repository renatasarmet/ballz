#include "jogo.h"

jogo::GameState jogo::estado_jogo = Inicializado;
sf::RenderWindow jogo::janela;
sf::Text jogo::timerText;
sf::Text jogo::totalText;
sf::Text jogo::nivelText;
sf::Text jogo::metaText;
sf::Sprite jogo::background;
bool pokeball::lancado = false;
braco::estado_braco braco::_estado_braco = Rotacionando;
double pokeball::dir = 0;
pokeball jogo::pokebola;
bool pokeball::colidiuOvo = false;
int jogo::rodadaAtual = 0;
bool pokeball::novaRodada = false;
sf::Text Nodetype::valorText;

// pokeball AINDA SENDO LANCADO NA TRANSICAO

void jogo::Start( Plano* plano, braco* hook)
{
    sf::Texture imagem;
    imagem.loadFromFile(resourcePath() + "imagens/fundo.jpg");
    background.setTexture(imagem); //DEFINE O BACKGROUND
    
    //Resetando as listas
    plano->DeletaTudo();

	//pokebola.set_posicao(225, 50);
    
    
    //Setando a rodada atual
    rodadaAtual = 1;
    
    plano->InsereNplano(rodadaAtual); // INICIALIZANDO O PLANO
    
    
    
   /* estado_jogo = jogo::Mostrando_Tela_Inicial;*/

    while (!IsExiting())
    {
        loop_jogo(plano, hook);
    }
    
    janela.close();
}

void jogo::CriandoTudo()
{
    
    
        
    
	janela.create(sf::VideoMode(450, 600), "PokeBallz", sf::Style::Close); //DEFINE TAMANHO DA JANELA, O QUE APARECE NO CABEÇALHO E FUNCOES DISPONIVEIS (FECHAR, RESIZE, MINIMIZAR)
   
    Plano plano;
	braco hook;
   
	estado_jogo = jogo::Mostrando_Tela_Inicial;
    jogo::Start(&plano, &hook);

	srand(time(NULL));
}

// LEMBRAR DE SETTAR O pokeball PARA NAO LANCADO

void jogo::JogarNovamente(Plano* plano, braco* hook)
{
	estado_jogo = jogo::Jogando;
	jogo::Start(plano, hook);
}

void jogo::novo_lancamento()
{
	//if (pokeball::lancado == false)
		//faz tudo


	//volta pra origem
//	pokebola.set_posicao(225, 50);
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
        case jogo::Ganhando:
        {
            mostrar_ganhou(plano, hook);
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
            
            imagem1.loadFromFile(resourcePath() + "imagens/pausar.png");
            botao_pausar.setTexture(imagem1);
            botao_pausar.setPosition(335, 3);

            verifica_colisao(plano, hook);
            
            
            if(pokeball::novaRodada){
                rodadaAtual += 1;
                cout << "NOVA RODADA : " << rodadaAtual << endl;
                pokeball::novaRodada = false;
                plano->InsereNplano(rodadaAtual);
            }
            
            janela.clear();
            janela.draw(background);
            hook->desenhar(janela);
            hook->update_todos();
			pokebola.desenhar(janela);
            plano->desenha_todos_plano(janela);
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
							estado_jogo = jogo::Mostrando_Menu;
      //                  else if(evento_atual.key.code == sf::Keyboard::F )
						//{
						//	pokebola.set_posicao(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y);
      //                      braco::_estado_braco = braco::Pokebola_Lancada;
      //                      pokeball::dir = (hook->get_rotacao() + 90)*0.0174532925;
      //                  }
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (evento_atual.mouseButton.button == sf::Mouse::Left && pokeball::lancado == false)
                            if (botao_pausar.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y))
                            {                                
								estado_jogo = jogo::Mostrando_Menu;
                            }

							else
							{
//								pokebola.set_posicao(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y);
								braco::_estado_braco = braco::Pokebola_Lancada;
								pokeball::dir = (hook->get_rotacao() + 90)*0.0174532925;
								
							}
						break;
					case sf::Event::MouseButtonReleased:
						novo_lancamento();
                        
					case sf::Event::MouseMoved:
						//hook->update(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y);
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
    tela_incial.Mostrar(janela);
    estado_jogo = jogo::Mostrando_Menu;
}

void jogo::mostrar_ganhou(  Plano* plano, braco* hook)
{
    Ganhou ganhou;
    Ganhou::ganhou resultado = ganhou.Mostrar(janela);
    switch (resultado)
    {
        case Ganhou::Sair:
            estado_jogo = jogo::Saindo;
            break;
        case Ganhou::Jogar_Novamente:
            jogo::JogarNovamente(plano, hook);
            break;
    }
}

void jogo::mostrar_perdeu(  Plano* plano, braco* hook)
{
    Perdeu perdeu;
    Perdeu::perdeu resultado = perdeu.Mostrar(janela);
    switch (resultado)
    {
        case Perdeu::Sair:
            estado_jogo = jogo::Saindo;
            break;
        case Perdeu::Jogar_Novamente:
            jogo::JogarNovamente(plano, hook);
            break;
    }
}

bool jogo::VerificaGanhou()
{
    if (true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
                       
//bool jogo::verifica_passou()
//{
//    if (total >= meta)
//    {
//        return true;
//    }
//    return false;
//}

void jogo::verifica_colisao( Plano* plano, braco* hook)
{
    Nodetype *Paux;
    bool ok = false;
    Paux = plano->PegaElementoN(1);
    
    while ((Paux != NULL) && (ok == false))
    {
        if (Paux->colidiu(hook->_pokeball))
        {
           
           // pokeball::lancado = false;
            braco::_estado_braco = braco::Acertou;
            //plano->ProcuraRemove(Paux->get_id(), ok); // NAO VAI SER ASSIM DEPOIS, TEM Q DIMINUIR O VALOR DO OVO
            cout << "TINHA VALOR = " << Paux->get_valor() << endl;
            if(Paux->get_valor()>1){
                Paux->set_valor(Paux->get_valor()-1);
                cout << "TENHO AGORA VALOR = " << Paux->get_valor() << endl;
            }
            else{
                plano->ProcuraRemove(Paux->get_id(), ok);
                cout << " REMOVI " << endl;
            }
            
            
            
            pokeball::colidiuOvo = true;
            
        }
        Paux = Paux->get_next();
    }
}

void jogo::mostrar_menu()
{
    Menu menu;
    Menu::menu_inicial resultado = menu.Mostrar(janela);
    switch (resultado)
    {
        case Menu::Sair:
            estado_jogo = jogo::Saindo;
            break;
        case Menu::Jogar:
            estado_jogo = jogo::Jogando;
            break;
        case Menu::Instrucoes:
            estado_jogo = jogo::Mostrando_Instrucao;
            break;
    }
}
                       
void jogo::mostrar_instrucao()
{
    Instrucoes instrucao;
    instrucao.set_k(1);
    int continua = 1;
    while (continua == 1) {
        Instrucoes::instrucoes_opcoes resultado = instrucao.Mostrar(janela);
        switch (resultado)
        {
            case Instrucoes::Menu:
                estado_jogo = jogo::Mostrando_Menu;
                continua = 0;
                break;
            case Instrucoes::Jogar:
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
    jogo::CriandoTudo();
    
    return 0;
}