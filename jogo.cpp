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


// pokeball AINDA SENDO LANCADO NA TRANSICAO

void jogo::Start(braco* hook, Plano* plano)
{
    sf::Texture imagem;
    imagem.loadFromFile("imagens/fundo.jpg");
    background.setTexture(imagem); //DEFINE O BACKGROUND
    
    //Resetando as listas
    plano->DeletaTudo();
    
    //plano->InsereNplano(20, todosItens, itensGanhar); // INICIALIZANDO O PLANO
    
    
   /* estado_jogo = jogo::Mostrando_Tela_Inicial;*/

    while (!IsExiting())
    {
        loop_jogo(hook, plano);
    }
    
    janela.close();
}

void jogo::CriandoTudo()
{
	janela.create(sf::VideoMode(450, 600), "Harry Potter e a Lista Sequencial", sf::Style::Close); //DEFINE TAMANHO DA JANELA, O QUE APARECE NO CABEÇALHO E FUNCOES DISPONIVEIS (FECHAR, RESIZE, MINIMIZAR)
 
    braco *hook = new braco();
   
    Plano plano;
   
	estado_jogo = jogo::Mostrando_Tela_Inicial;
    jogo::Start(hook, &plano);

}

// LEMBRAR DE SETTAR O pokeball PARA NAO LANCADO

void jogo::JogarNovamente(braco* hook, Plano* plano)
{
	estado_jogo = jogo::Jogando;
	jogo::Start(hook, plano);
}
                                    
bool jogo::IsExiting()
{
    if (estado_jogo == jogo::Saindo)
        return true;
    else
        return false;
}

void jogo::loop_jogo(braco* hook, Plano* plano)
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
            mostrar_ganhou(hook, plano);
            break;
        }
        case jogo::Perdendo:
        {
            mostrar_perdeu(hook, plano);
            break;
        }
        case jogo::Jogando:
        {
            sf::Event evento_atual;
            sf::Sprite botao_pausar;
            sf::Texture imagem1;
            
            imagem1.loadFromFile("imagens/pausar.png");
            botao_pausar.setTexture(imagem1);
            botao_pausar.setPosition(335, 13);

            //verifica_colisao(hook, plano);
            
            janela.clear();
            janela.draw(background);
            hook->desenhar(janela);
            hook->update_todos();
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
                        else if(evento_atual.key.code == sf::Keyboard::F && pokeball::lancado == false)
						{
                            braco::_estado_braco = braco::Pokebola_Lancada;
                            pokeball::dir = (hook->get_rotacao() + 90)*0.0174532925;
                        }
                        break;
                    case sf::Event::MouseButtonPressed:
                        if (evento_atual.mouseButton.button == sf::Mouse::Left)
                            if (botao_pausar.getGlobalBounds().contains(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y))
                            {                                
								estado_jogo = jogo::Mostrando_Menu;
                            }
						break;
					case sf::Event::MouseMoved:
						hook->update(sf::Mouse::getPosition(janela).x, sf::Mouse::getPosition(janela).y);
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

void jogo::mostrar_ganhou(braco *hook, Plano* plano)
{
    Ganhou ganhou;
    Ganhou::ganhou resultado = ganhou.Mostrar(janela);
    switch (resultado)
    {
        case Ganhou::Sair:
            estado_jogo = jogo::Saindo;
            break;
        case Ganhou::Jogar_Novamente:
            jogo::JogarNovamente(hook, plano);
            break;
    }
}

void jogo::mostrar_perdeu(braco *hook, Plano* plano)
{
    Perdeu perdeu;
    Perdeu::perdeu resultado = perdeu.Mostrar(janela);
    switch (resultado)
    {
        case Perdeu::Sair:
            estado_jogo = jogo::Saindo;
            break;
        case Perdeu::Jogar_Novamente:
            jogo::JogarNovamente(hook, plano);
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

//void jogo::verifica_colisao(braco* hook, Plano* plano)
//{
//    Nodetype *Paux;
//    bool ok = false;
//    Paux = plano->PegaElementoN(1);
//    
//    while ((Paux != NULL) && (ok == false))
//    {
//        if (Paux->colidiu(hook->_pokeball))
//        {
//            switch (Paux->get_tipo())
//            {
//                case 1:
//                    if (hook->_pokeball.get_tipo() == 2)
//                        total -= 200;
//                    else
//                        total += Paux->get_valor();
//                    break;
//                case 2:
//                    if (hook->_pokeball.get_tipo() == 2)
//                        total += Paux->get_valor();
//                    else
//                        total -= 500;
//                    break;
//                case 3:
//                    if (hook->_pokeball.get_tipo() == 2)
//                        estado_jogo = Perdendo;
//                    else
//                    {
//                        total += Paux->get_valor();
//                        itensGanhar->ProcuraRemove(Paux->get_info(), ok, destruidos, todosItens);  // ACHO QUE O ERRO ESTA AQUI
//                    }
//                    break;
//                case 4:
//                    if (hook->_pokeball.get_tipo() == 2)
//                        total += Paux->get_valor();
//                    break;
//				case 5:
//					if (hook->_pokeball.get_tipo() == 2)
//						estado_jogo = Perdendo;
//					else
//					{
//						total += Paux->get_valor();
//						voldemort_morreu = true;
//					}
//                default:
//                    break;
//            }
//            pokeball::lancado = false;
//            braco::_estado_braco = braco::Acertou;
//            plano->ProcuraRemove(Paux->get_id(), ok);
//            totalText.setString("$ " + to_string(total));
//        }
//        Paux = Paux->get_next();
//    }
//}

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