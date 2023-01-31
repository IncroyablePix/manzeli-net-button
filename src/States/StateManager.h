#ifndef MANZELI_NET_BUTTON_STATEMANAGER_H
#define MANZELI_NET_BUTTON_STATEMANAGER_H

#include <memory>
#include <stack>
#include "IState.h"

class StateManager
{
public:
    StateManager();
    void PushState(std::unique_ptr<IState> state);
    void PopState();
    void Update();
    bool IsWakeUpBoot();
    void Sleep() const;

private:
    std::stack<std::unique_ptr<IState>> m_states;
};


#endif //MANZELI_NET_BUTTON_STATEMANAGER_H
