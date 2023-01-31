#ifndef MANZELI_NET_BUTTON_ISTATE_H
#define MANZELI_NET_BUTTON_ISTATE_H

class IState
{
public:
    virtual ~IState() = default;
    virtual void OnResume() = 0;
    virtual void OnStart() = 0;
    virtual void OnStop() = 0;
    virtual void Update() = 0;
};


#endif //MANZELI_NET_BUTTON_ISTATE_H
