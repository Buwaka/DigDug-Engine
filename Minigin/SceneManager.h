#pragma once
#include "Singleton.h"
#include "Minigin.h"

namespace mini
{
	struct FixedTimeRegistration
	{
		Duration Timer;
		Duration Interval;
		//int ID; verwijzing naar update
	};


	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		//returns ID
		unsigned int CreateScene(const std::string& name, Scene** Out, bool focus = false);
		//returns ID
		unsigned int RegisterScene(Scene* scene, bool focus = false);

		void FocusScene(unsigned int ID);

		void Initialize();
		void Update();
		void FixedUpdate();
		void Render();

	protected:
		friend Minigin;
		void Clean();

	private:
		Scene* CurrentScene = nullptr;
		std::vector<Scene*> Scenes;


	};
}
