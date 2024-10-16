#pragma once

#include "Component/Input.h"
#include "GLFW/glfw3.h"
#include <memory>
#include <vector>

namespace Creyon {

	class EventPublisher {
	private:
		std::vector<std::shared_ptr<Subscriber>> m_subscriberList;
		std::unordered_map<int, bool> m_keyStates;
		float m_lastCursorX, m_lastCursorY, m_firstMouse, m_sensitivity;

	public:

		EventPublisher();

		void setKeyState(int key, bool state) {
			m_keyStates[key] = state;
		}

		void addSubscriber(const std::shared_ptr<Subscriber>& subscriber);

		void notifyKeyboard(float deltaTime);

		void notifyCursor(float cursorX, float cursorY);

		void notifyMouseScroll(float offsetX, float offsetY);

	};
}
