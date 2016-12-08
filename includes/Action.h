//
// Created by ptdave on 12/8/16.
//

#ifndef INNER_ACTION_H
#define INNER_ACTION_H

#include <string>
#include <map>

class OnAction {
private:
    bool done;
public:
    bool isDone() const {
        return done;
    }

    void setDone(bool done) {
        OnAction::done = done;
    }

    const std::string &getDo_what() const {
        return do_what;
    }

    void setDo_what(const std::string &do_what) {
        OnAction::do_what = do_what;
    }

    const std::map<std::string, std::string> &getActions() const {
        return actions;
    }

    void setActions(const std::map<std::string, std::string> &actions) {
        OnAction::actions = actions;
    }

private:
    std::string do_what;
    std::map<std::string, std::string> actions;
};


#endif //INNER_ACTION_H
