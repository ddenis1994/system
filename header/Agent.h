#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent();
    static Agent * createAgent(std::pair<std::string,int> & agent);

    virtual void act(Session& session)=0;
};

class ContactTracer: public Agent{
public:
    ContactTracer();

    virtual void act(Session& session);
};


class Virus: public Agent{
public:
    Virus(int nodeInd);

    virtual void act(Session& session);
private:
    const int nodeInd;
};

#endif