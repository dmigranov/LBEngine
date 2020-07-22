﻿#include <pch.h>

#include "Game.h"
#include "Scene.h"
#include "Camera.h"

#include "ResourceManager.h"
#include "InputComponent.h"

#include "Entity.h"

// Components
#include "ComponentType.h"
#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "InputHandlerComponent.h"
#include "BitmapComponent.h"
#include "CameraComponent.h"

// Systems
#include "TransformUpdateSystem.h"
#include "InputSystem.h"
#include "BitmapRenderSystem.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;


// Entry point
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int nCmdShow)
{
    Game& game = Game::GetInstance();
    game.InitializeEngine(hInstance, nCmdShow, L"Сф. и Элл. Пространства", false, false);
    game.SetBackgroundColor(DirectX::Colors::PowderBlue);   //todo: перенести
    Scene* scene = game.GetScene();
    auto resourceManager = game.GetResourceManager(); 

    
    Texture* asphaltTexture = resourceManager->CreateTexture(L"cat.dds");


    {
        scene->AddSystem(new InputSystem());
        scene->AddSystem(new BitmapRenderSystem());
    }

    //todo: изменить InputSystem
    //InputInfo -> InputComponent. Задумка: 
    //I would create an input componentand various other action components, like walk, jump, crawl, weapon, etc.The input component would have fields that describe how the entity wants to move, such as : walk left, jump, and attack.This can be supplied by the keyboard, by an AI, or over the network, which is implemented as a control component.
    //The control systems - there is one for each control component type(keyboard, gamepad, network, AI, etc.); they set fields of the input component
    //The action systems - there is one for each action component type(walk, jump, attack, interact, etc.); they look at the fields of the input componentand modify the physics state, weapon component, etc.
    //Тогда у InputHandler не будет зависимости от ускорения, сил...
    //Если надо для Jump - ок
    //Можно даже эти action systems реализовать в виде лямбд
    //наследоваться от ActionSystem, выбирать нужные компоненты и лямбдить экшн

    Entity* cameraEntity = new Entity("camera");
    auto cameraTransform = new TransformComponent(1, 0, -1, 0, 0, 0);
    cameraEntity->SetTransform(cameraTransform);
    auto cameraInputComponent = new InputComponent();
    cameraEntity->AddComponent(ComponentType::InputComponentType, cameraInputComponent);
    /*cameraEntity->AddComponent(ComponentType::InputHandlerComponentType, new InputHandlerComponent([](Entity* pEntity, DWORD deltaTime, InputComponent& input) {
       static double m_movementGain = 0.003;
       static double m_rotationGain = 0.004;
        
        auto pTransform = pEntity->GetTransform();
        auto kbs = input.GetKeyboardState();
        auto ms = input.GetMouseState();

        if (ms.leftButton)
        {
            Vector3 delta = Vector3(float(ms.x), float(ms.y), 0.f);
            pTransform->Rotate(Vector3(delta.y, delta.x, 0.) * deltaTime * m_rotationGain);
        }

        Vector3 fwd = pTransform->GetForward() * deltaTime * m_movementGain;
        Vector3 right = pTransform->GetRight() * deltaTime * m_movementGain;

        if (kbs.W)
            pTransform->Move(fwd);
        if (kbs.S)
            pTransform->Move(-fwd);
        if (kbs.A)
            pTransform->Move(-right);
        if (kbs.D)
            pTransform->Move(right);
        if (kbs.D1)
            pEntity->SetTransform(cameraTransform1);
        else if (kbs.D2)
            pEntity->SetTransform(cameraTransform2);
    }));*/
    scene->AddEntity(cameraEntity);
    auto cameraComponent = new CameraComponent(true);
    cameraEntity->AddComponent(ComponentType::CameraComponentType, cameraComponent);
    scene->SetCamera(cameraEntity);

    auto bitmap = new BitmapComponent(1, 1, asphaltTexture, false);

    Entity* e1 = new Entity();
    auto transform1 = new TransformComponent(0, 0, 1, 0, 0, 0, 0.3, 0.3, 0.3);
    e1->SetTransform(transform1);
    /*e1->AddComponent(ComponentType::InputHandlerComponentType, new InputHandlerComponent([](Entity * pEntity, DWORD deltaTime, InputComponent &input) {
        auto pTransform = pEntity->GetTransform();
        auto kb = input.GetKeyboardState();
        if (kb.Up)
            pTransform->Move(0., 0.01, 0.);
        if (kb.Down)
            pTransform->Move(0., -0.01, 0.);
    }));*/
    e1->AddComponent(ComponentType::BitmapComponentType, bitmap);
    scene->AddEntity(e1);

    auto transform2 = new TransformComponent(0, 0.3, 2, 0, 0, XM_PI/4, 0.3, 0.3, 0.3);
    Entity* e2 = new Entity();
    e2->SetTransform(transform2);
    e2->AddComponent(ComponentType::BitmapComponentType, bitmap);
    scene->AddEntity(e2);

    return game.StartGame();
}
    









/*{
    game.MoveCamera(Vector3(0, 0, -XM_PI / 4));
    game.SetCameraFovY(XM_PI / 2);
    game.SetBackgroundColor(DirectX::Colors::PowderBlue);

    auto earthTexture = game.CreateTexture(L"earth.dds");
    auto asteroidTexture = game.CreateTexture(L"asteroid2.dds");
    auto fabricTexture = game.CreateTexture(L"fabric.dds");
    auto sviborgTexture = game.CreateTexture(L"sviborg.dds");
    auto fireTexture = game.CreateTexture(L"fire.dds");
    auto moonTexture = game.CreateTexture(L"moon.dds");
    if (!earthTexture || !moonTexture || !asteroidTexture || !fireTexture || !sviborgTexture || !fabricTexture)
    {
        MessageBox(nullptr, TEXT("Failed to load textures."), TEXT("Error"), MB_OK);
        return 1;
    }

    auto mesh1 = new SphericalSphere(0.15f, 20, 20, earthTexture);
    //auto mesh1 = new SphericalEllipsoid(0.9999f, 0.55f, 0.45f, 40, 40, asteroidTexture);

    mesh1->AddUpdater(Mesh::MeshUpdater([&game](Matrix in, float delta) {
        auto ks = Keyboard::Get().GetState();
        float gain = 0.045f;
        Matrix m = Matrix::Identity;
        if (ks.U)
            m = SphericalRotationYW(-gain);
        if (ks.J)
            m = SphericalRotationYW(gain);
        if (ks.H)
            m = SphericalRotationXW(gain);
        if (ks.K)
            m = SphericalRotationXW(-gain);
        return  in *  m;  //так всегда вверх!
    }));
    game.AddMesh(mesh1);


    for (int i = 1; i < 8; i++)
    {
        Mesh* mesh = new SphericalSphere(0.15f, 20, 20, earthTexture, SphericalRotationZW(i * XM_PI / 8));
        game.AddMesh(mesh);
    }


    auto moon = new SphericalSphere(0.05f, 20, 20, moonTexture, SphericalRotationZW(-0.39f));
    moon->SetParent(mesh1);
    moon->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
        return in * SphericalRotationXZ(delta);
    }));
    game.AddMesh(moon);


    auto asteroid = new SphericalSphere(0.02f, 20, 20, asteroidTexture, SphericalRotationZW(-0.1f));
    asteroid->SetParent(moon);
    asteroid->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
        return in * SphericalRotationXZ(7 * delta);
    }));
    game.AddMesh(asteroid);


    auto head = new SphericalSphere(0.08f, 20, 20, sviborgTexture);
    head->AddUpdater(Mesh::MeshUpdater([](Matrix in, float delta) {
        auto ks = Keyboard::Get().GetState();

        static double time = 0;
        if (!ks.Space)
            time += delta;

        return SphericalRotationYW(-0.15f) * SphericalRotationXZ(XM_PI / 2) * SphericalRotationZW(time / 5.) * SphericalRotationYW(0.03 * sin(7 * time));

    }));
    game.AddMesh(head);

    int sect = 8;
    for (int i = 0; i < sect; i++)
    {
        Mesh* mesh = new SphericalSphere(0.01f, 20, 20, fireTexture, SphericalRotationYW(-0.12f) * SphericalRotationYZ(i * XM_2PI / sect));
        mesh->AddUpdater(SphericalMesh::MeshUpdater([i](Matrix in, float delta) {
            return  in * SphericalRotationYZ(delta / 3.f);
        }));
        mesh->SetParent(head);
        game.AddMesh(mesh);
    }


    auto mesh2 = SphericalMeshLoader::LoadMesh("mesh3.sph");
    mesh2->SetTexture(fabricTexture);
    mesh2->SetWorldMatrix(SphericalRotationYZ(XM_PIDIV2) * SphericalRotationYW(0.09f));
    game.AddMesh(mesh2);

}*/

/*

    MeshComponent::VertexPosTex vertices[8] = {
        { XMFLOAT4(-1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT2(0, 0) }, // 0
        { XMFLOAT4(-1.0f,  1.0f, -1.0f, 1.0f), XMFLOAT2(0, 1) }, // 1
        { XMFLOAT4(1.0f,  1.0f, -1.0f, 1.0f), XMFLOAT2(1, 1)}, // 2
        { XMFLOAT4(1.0f, -1.0f, -1.0f, 1.0f), XMFLOAT2(1, 0)}, // 3
        { XMFLOAT4(-1.0f, -1.0f,  1.0f, 1.0f),  XMFLOAT2(0, 0) }, // 4
        { XMFLOAT4(-1.0f,  1.0f,  1.0f, 1.0f), XMFLOAT2(0, 1)}, // 5
        { XMFLOAT4(1.0f,  1.0f,  1.0f, 1.0f), XMFLOAT2(1, 1) }, // 6
        { XMFLOAT4(1.0f, -1.0f,  1.0f, 1.0f), XMFLOAT2(0, 1) }  // 7
    };

    WORD indices[36] =
    {
        0, 1, 2, 0, 2, 3,
        4, 6, 5, 4, 7, 6,
        4, 5, 1, 4, 1, 0,
        3, 2, 6, 3, 6, 7,
        1, 5, 6, 1, 6, 2,
        3, 4, 0, 7, 4, 3
    };
    auto m = new MeshComponent(8, vertices, 36, indices);

*/