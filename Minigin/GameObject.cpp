#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

unsigned int mini::GameObject::ID = 0;

mini::GameObject::GameObject(std::string name, Scene* scene)
{
	Components = std::vector<ObjectComponent*>();
	ParentScene = scene;

	AddComponent(new TransformComponent());

	if (name == NamePlaceholder)
		Name = "ID: " + std::to_string(ID) + " ";
	else
		Name = name;

	ID++;
}

mini::GameObject::~GameObject()
{
	for (ObjectComponent* comp : Components)
	{
		delete comp;
	}

	for (GameObject* comp : Children)
	{
		comp->SetParent(Parent);
	}
}

void mini::GameObject::AddComponent(ObjectComponent* comp)
{
	Components.push_back(comp);
	comp->GameObject = this;
	comp->Initialize();
}

void mini::GameObject::SetParent(GameObject * parent)
{
	Parent = parent;
}

void mini::GameObject::SetRenderPosition(int pos)
{
	auto trans = GetComponent<TransformComponent>();
	if (trans)
	{
		trans->SetZposition(pos);
	}

	RenderPosition = pos;
}

int mini::GameObject::GetRenderPosition() const
{
	return RenderPosition;
}

mini::GameObject* mini::GameObject::GetParent()
{
	return Parent;
}

void mini::GameObject::SetName(std::string name)
{
	Name = name;
}

std::string const & mini::GameObject::GetName() const
{
	return Name;
}

mini::Scene * mini::GameObject::GetScene()
{
	return ParentScene;
}

void mini::GameObject::Destroy()
{
	if(ParentScene)
		ParentScene->RemoveObject(this);
}

bool mini::GameObject::ObjectInitialize()
{
#ifdef _DEBUG 
	Done = false;
#endif // _DEBUG 

	Initialize();

#ifdef _DEBUG 
	Done = true;
	return Done;
#else
	return true;
#endif // _DEBUG 
}

bool mini::GameObject::ObjectUpdate()
{
#ifdef _DEBUG 
	Done = false;
#endif // _DEBUG 

	Update();
	for (ObjectComponent* comp : Components)
	{
		comp->Update();
	}

#ifdef _DEBUG 
	Done = true;
	return Done;
#else
	return true;
#endif // _DEBUG 


}

bool mini::GameObject::ObjectLateUpdate()
{

#ifdef _DEBUG 
	Done = false;
#endif // _DEBUG 

	LateUpdate();
	for (ObjectComponent* comp : Components)
	{
		comp->LateUpdate();
	}

#ifdef _DEBUG 
	Done = true;
	return Done;
#else
	return true;
#endif // _DEBUG 
}

bool mini::GameObject::ObjectFixedUpdate()
{
#ifdef _DEBUG 
	Done = false;
#endif // _DEBUG 

	FixedUpdate();
	for (ObjectComponent* comp : Components)
	{
		comp->FixedUpdate();
	}

#ifdef _DEBUG 
	Done = true;
	return Done;
#else
	return true;
#endif // _DEBUG 
}

void mini::GameObject::ObjectDraw() const
{
	Draw();
	for (ObjectComponent* comp : Components)
	{
		comp->Draw();
	}
}

void mini::GameObject::ObjectPostDraw() const
{
	PostDraw();
	for (ObjectComponent* comp : Components)
	{
		comp->PostDraw();
	}
}


