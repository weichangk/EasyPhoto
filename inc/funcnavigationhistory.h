#pragma once

#include <QUndoStack>

class FuncNavigationHistory {
public:
    void executeCommand(const QString &prev, const QString &curr, std::function<void(QString)> func);
    void undo();
    void redo();
    QUndoStack *getUndoStack();

private:
    QUndoStack m_rUndoStack;
};
