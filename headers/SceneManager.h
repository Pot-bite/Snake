#pragma once
#include <memory>
#include "Scene.h"

class SceneManager
{
public:
    static SceneManager& getInstance() {
        static SceneManager instance;
        return instance;
    }


    void SetWindow(sf::RenderWindow* window) { m_window = window; }
    void SetActiveScene(std::unique_ptr<Scene> newScene);
    void Update(float deltaTime, sf::RenderWindow& m_window);
    void Render(sf::RenderWindow& window);
    void HandleEvent(const sf::Event& event);
    sf::RenderWindow* GetWindow() const { return m_window; }

    Scene* GetActiveScene() const;

private:
    SceneManager() = default;
    ~SceneManager() = default;

    std::unique_ptr<Scene> m_activeScene;

    std::unique_ptr<Scene> m_currentScene;
    sf::RenderWindow* m_window = nullptr;
   
};