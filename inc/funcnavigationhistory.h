#pragma once
#include "funcenum.h"

#include <QUndoStack>

class FuncNavigationHistory {
public:
    void executeCommand(EFunc prev, EFunc curr, std::function<void(EFunc)> func);
    void undo();
    void redo();
    QUndoStack *getUndoStack();

private:
    QUndoStack m_rUndoStack;
};
