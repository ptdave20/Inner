//
// Created by ptdave on 12/8/16.
//

#ifndef INNER_ACTION_H
#define INNER_ACTION_H

#include <string>
#include <map>

class OnAction {
public:
    bool isDone() const {
        return done;
    }

    void setDone(bool done) {
        OnAction::done = done;
    }

    const std::map<std::string, std::string> &getActions() const {
        return actions;
    }

    void setActions(const std::map<std::string, std::string> &actions) {
        OnAction::actions = actions;
    }

    operator Json::Value() {
		Json::Value ret;
		for (const auto &action : actions) {
			Json::Value act;
			act[action.first] = action.second;
			ret.append(ret);
		}
		return ret;
	}
private:
    std::map<std::string, std::string> actions;
	bool done;
};


#endif //INNER_ACTION_H
