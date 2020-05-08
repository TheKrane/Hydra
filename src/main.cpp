#include <iostream>
#include <cmath>

#include <RenderSystem.hpp>
#include <PhysicsSystem.hpp>
#include <InputSystem.hpp>
#include <LogicSystem.hpp>

#include <Entity.hpp>
#include <Shader.hpp>
#include <MeshRenderComponent.hpp>
#include <LightComponent.hpp>
#include <CameraComponent.hpp>
#include <CallbackLogicComponent.hpp>

#include <glm/glm.hpp>

//Declare global systems
RenderSystem* g_pRenderSystem = nullptr;
PhysicsSystem* g_pPhysicsSystem = nullptr;
InputSystem* g_pInputSystem = nullptr;
LogicSystem* g_pLogicSystem = nullptr;

int main()
{
	//Initialize systems
	try {
		g_pRenderSystem = new RenderSystem("Hydra Demo", 1280, 720);
		g_pPhysicsSystem = new PhysicsSystem();
		g_pInputSystem = new InputSystem();
		g_pLogicSystem = new LogicSystem();
	} catch(const std::exception& e) {
		std::cout << e.what() << std::endl;
		return -1;
	}

	//Setup input
	g_pInputSystem->BindButton("Space", SDL_SCANCODE_SPACE);

	//Load content
	Shader* pStandardShader = g_pRenderSystem->CreateShader("data/StandardShader");

    Texture grassTexture("data/grass.jpg");

	Material defaultMaterial(pStandardShader);
    defaultMaterial.SetAttribute("Color", glm::vec4(1.0));
    defaultMaterial.SetAttribute("Ambient", 1.0f);
    defaultMaterial.SetAttribute("Diffuse", 1.0f);
    defaultMaterial.SetAttribute("Specular", 0.5f);
	defaultMaterial.SetTextureAttribute("DiffuseTexture", grassTexture);

	Entity cube;
	cube.SetRotation(glm::quat(glm::vec3(0.0f, 0.1f, 45.0f)));
	MeshRenderComponent cubeMeshComponent;
	cubeMeshComponent.SetMaterial(&defaultMaterial);
	cubeMeshComponent.LoadMeshFromObj("data/cube.obj");
	cube.AddComponent(&cubeMeshComponent);

	Entity pointLight;
	pointLight.SetPosition(glm::vec3(0.0f, 0.0f, -5.0f));
	LightComponent pointLightComponent(LightType::PointLight, 0);
	pointLight.AddComponent(&pointLightComponent);

	Entity camera;
	camera.SetPosition(glm::vec3(0.0f, 0.5f, -2.0f));
	CameraComponent cameraComponent;
	camera.AddComponent(&cameraComponent);
	g_pRenderSystem->SetMainCameraComponent(&cameraComponent);


	//Main loop
	bool quit = false;
	while(!quit)
	{
		//Handle events
		g_pRenderSystem->HandleEvents(&quit);

		//Custom logic
		if(g_pInputSystem->GetButtonDown("Space"))
			cube.SetPosition(cube.GetPosition() + glm::vec3(0.1f, 0.0f, 0.0f));

		//Update
		g_pInputSystem->Update();
		g_pLogicSystem->Update();
		g_pPhysicsSystem->Update();

		//Render
		g_pRenderSystem->Render();
	}

	//Shutdown
	delete g_pLogicSystem;
	g_pLogicSystem = nullptr;
	
	delete g_pInputSystem;
	g_pInputSystem = nullptr;
	
	delete g_pPhysicsSystem;
	g_pPhysicsSystem = nullptr;
	
	delete g_pRenderSystem;
	g_pRenderSystem = nullptr;

	return 0;
}
