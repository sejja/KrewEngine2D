#include "Engine.h"

//Additional include files
#include "System.h"
#include "Game.h"

#ifndef _DELETEMACRO_H
#include "deletemacros.h"
#endif
#ifndef _STRING_H
	#include "string.h"
#endif

EngineState Engine::m_EngineState = EngineState::Invalid;

Engine::Engine()
{
	m_EngineState = EngineState::Constructing;
}

//Public Methods
int Engine::RunLoop() {
	Context context;

	if (!this->Initialize())
		return 0;

	srand(GetTickCount());

	MSG msg = {};

	m_EngineState = EngineState::Running;

	while (msg.message != WM_QUIT && m_EngineSlate == EngineSlate::Running) {
		//CheckResize();

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		this->Update(context);
		this->Draw(context);
		}

		//Logger::Log("Ending the program");
		//Logger::WriteLogFile();

		if(this->ShutDown())
			return 0;

		return msg.wParam;
}

//Private Method
Engine::~Engine()
{
	m_EngineState = EngineState::Destroying;
}

int Engine::Initialize() {
	m_EngineState = EngineState::Initializing;

	Game* game = CreateGame();

	if (!game)
		return false;

		//Add some systems

		return true;
}

int Engine::Draw(const Context& context) {
	return true;
}

int Engine::Update(const Context& context) {
	return true;
}

int Engine::ShutDown() {
	m_EngineState = EngineState::ShuttingDown;

	for (std::pair<SystemType, System*> psys : m_mapSystems) {
		//if (!psys.second->ShutDown()){
			//Log::Logger("Failed to shutdown system: " + psys->GetSystemType());
			//continue;
		//}

		SafeDelete(psys.second);
	}

	return true;
}


int AddSystem(System* psys) {
	//auto element = m_mapSystems.insert(std::make_pair(psys->GetType(), psys));
	//if (element.second)
		//return true;

	return false;
}


Game* CreateGame() {
	if (!AddSystem(new Game(GameData())))
		return nullptr;
	Game* game = GetSystem<Game>(SystemType::Sys_Game);
	if (!game)
		return nullptr;

	//if(!game->Initialize())
	//	return nullptr;

	return game;
}
