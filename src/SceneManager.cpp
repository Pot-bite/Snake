#include "SceneManager.h"

void SceneManager::SetActiveScene(std::unique_ptr<Scene> newScene) {
    m_currentScene = std::move(newScene);
    if (m_currentScene && m_window) {
        m_currentScene->Start(*m_window);
    }
}

void SceneManager::Update(float deltaTime, sf::RenderWindow& m_window){
    if (m_currentScene) {
        m_currentScene->Update(deltaTime, m_window);
    }
}

void SceneManager::Render(sf::RenderWindow& window) {
    if (m_currentScene) {
        m_currentScene->Render(window);
    }
}

void SceneManager::HandleEvent(const sf::Event& event) {
    if (m_currentScene) {
        m_currentScene->HandleEvent(event);
    }
}