#ifndef MODELSWRAPPER_P_H
#define MODELSWRAPPER_P_H

#include <QScopedPointer>
#include <tables/alltables.h>

class DiaryTables;

enum class TableType;

class DiaryTablesPrivate
{
    friend class DiaryTables;
    DiaryTables* q;

private:
    DiaryTablesPrivate(DiaryTables* qPtr);

    SqlTableModel* initTable(TableType tableType );

    template<typename TablePtr>
    SqlTableModel* initTable(TablePtr* &dest);

    ArchersTableModel* m_archers = nullptr;
    ArrowsTableModel* m_arrows = nullptr;
    BowsTableModel* m_bows = nullptr;
    ScopesTableModel* m_scopes = nullptr;
    TrainingTableModel* m_trainings = nullptr;
    RecordTableModel* m_records = nullptr;
    TrainingStandardModel* m_trainingStandards = nullptr;
    StandardModel* m_standards = nullptr;
    StandardExcerciseModel* m_standardExcersices = nullptr;
    ExcerciseModel* m_excersices = nullptr;
    TargetModel* m_targets = nullptr;
    ShotModel* m_shots = nullptr;
    SimpleShotModel* m_simpleShots = nullptr;

    QScopedPointer< QSqlDatabase > m_db;

};

#endif // MODELSWRAPPER_P_H
