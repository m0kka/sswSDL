#include "Test.h"

SpriteAnimated* wizard = new SpriteAnimated;


std::vector<Renderable*> operator+(std::vector<Sprite*> v1, const std::vector<Text*>& v2)
{
	std::vector<Renderable*> vec;
	for (int i = 0; i < v1.size(); i++)
		vec.push_back(v1.at(i));
	vec.insert(vec.end(), v2.begin(), v2.end());
	return vec;
}


void Test::handleEvents()
{
	while (SDL_PollEvent(&m_Event)) {
		if (m_Event.type == SDL_QUIT)
			Game::setNextState(GAMESTATE_EXIT);
		else if (m_Event.type == SDL_KEYDOWN) {

			switch (m_Event.key.keysym.sym) {

			case SDLK_w:
			case SDLK_UP:
				wizard->move(0, -5);
				wizard->setAnimation(GameSettings::GAME_RESOURCEPATH + "wizardStandRight.xml");

				m_TSTest++;
				if (m_TSTest > TSR->getAmountTiles() - 1)
					m_TSTest = 0;

				TSR->setTile(m_TSTest);

				break;
			case SDLK_s:
			case SDLK_DOWN:
				wizard->move(0, 5);
				wizard->setAnimation(GameSettings::GAME_RESOURCEPATH + "wizardStandLeft.xml");
				break;
			case SDLK_a:
			case SDLK_LEFT:
				wizard->move(-5, 0);
				wizard->setAnimation(GameSettings::GAME_RESOURCEPATH + "wizardWalkingLeft.xml");
				break;
			case SDLK_d:
			case SDLK_RIGHT:
				wizard->move(5, 0);
				wizard->setAnimation(GameSettings::GAME_RESOURCEPATH + "wizardWalkingRight.xml");
				break;
			}
		}

		for each (UI* ui in m_UIs) {
			ui->handleInput(m_Event);
		}
	}
}

void Test::logic()
{
	Uint64 now = SDL_GetPerformanceCounter();
	double deltaTime = ((now - m_TextTimer) * 1000 / (double)SDL_GetPerformanceFrequency());

	if (deltaTime > 1000) {

		m_TextIndex++;

		if (m_TextIndex > 1)
			m_TextIndex = 0;

		m_TextTimer = SDL_GetPerformanceCounter();
	}

//	m_Texts.at(0)->setText(m_TextEntries[m_TextIndex]);


	//-----------

	m_Angle++;

	if (m_Angle > 36000)
		m_Angle = 0;

	int x = (int)(200 * cos((double)m_Angle / 100));
	int y = (int)(200 * sin((double)m_Angle / 100));

	SDL_SetWindowPosition(Game::getInstance()->getWindow(), x + 500, y + 300);
}

void Test::render()
{
	SDL_RenderClear(Game::getRenderer());
	for each (Renderable* renderable in m_Renderables)
	{
		renderable->draw();
	}

	for each (UI* ui in m_UIs) {
		ui->draw();
	}
	
	SDL_RenderPresent(Game::getRenderer());
}

Test::Test()
{
	wizard = new SpriteAnimated(Game::getRenderer(), GameSettings::GAME_RESOURCEPATH + "wizardStandLeft.xml");
	m_Sprites.push_back(wizard);
//	m_Texts.push_back(new Text(Game::getRenderer(), Game::GAME_RESOURCEPATH + "sample.ttf", "Hi!"));
//	m_Texts.push_back(new Text(Game::getRenderer(), GameSettings::GAME_RESOURCEPATH + "alagard.ttf", " "));

	wizard->setScale(10);
	wizard->renderAtPos(true);
	wizard->setAnchor(Sprite::Anchor::CENTRE);

	m_Renderables = m_Sprites + m_Texts;

	UI* test = new UI(UI::UIAnchor::BOTTOM_LEFT, GameSettings::GAME_RESOURCEPATH + "ui_01.xml");
	
	m_UIs.push_back(test);


	m_TextTimer = SDL_GetPerformanceCounter();
	m_TextIndex = 0;

	TiledSprite* tester = new TiledSprite(GameSettings::GAME_RESOURCEPATH + "tilesheet_01.xml");
	m_Renderables.push_back(tester);
	TSR = tester;
	m_Timer = Game::getTimer();

}


Test::~Test()
{
}
