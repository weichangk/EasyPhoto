#pragma once
#include "funcenum.h"

#include <QUndoCommand>

class FuncNavigateCommand : public QUndoCommand {
public:
    FuncNavigateCommand(EFunc prev, EFunc curr, std::function<void(EFunc)> func);
    void undo() override;
    void redo() override;

private:
    EFunc m_ePreviousFunc;
    EFunc m_eCurrentFunc;
    std::function<void(EFunc)> m_pNavigateFunc;
};