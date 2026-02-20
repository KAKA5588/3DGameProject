//#include "EnemyStateMachine.h"
//#include "Enemy.h"
//#include "EnemyPerception.h"
//
//EnemyStateMachine::EnemyStateMachine(Enemy* owner)
//    : enemy(owner), currentState(EnemyState::Idle), stateTimer(0.0f)
//{
//}
//
//void EnemyStateMachine::Update(float dt)
//{
//    stateTimer += dt;
//
//    switch (currentState)
//    {
//    case EnemyState::Idle:     UpdateIdle(dt); break;
//    case EnemyState::Patrol:   UpdatePatrol(dt); break;
//    case EnemyState::Alert:    UpdateAlert(dt); break;
//    case EnemyState::Chase:    UpdateChase(dt); break;
//    case EnemyState::Search:   UpdateSearch(dt); break;
//    case EnemyState::Attack:   UpdateAttack(dt); break;
//    case EnemyState::Cooldown: UpdateCooldown(dt); break;
//    case EnemyState::Hit:      UpdateHit(dt); break;
//    case EnemyState::Return:   UpdateReturn(dt); break;
//    case EnemyState::Dead:     break;
//    }
//}
//
//void EnemyStateMachine::ChangeState(EnemyState state)
//{
//    currentState = state;
//    stateTimer = 0.0f;
//}
//
//EnemyState EnemyStateMachine::GetState() const
//{
//    return currentState;
//}
//
//// ---------------- ó‘Ôˆ— ----------------
//
//void EnemyStateMachine::UpdateIdle(float)
//{
//    ChangeState(EnemyState::Patrol);
//}
//
//void EnemyStateMachine::UpdatePatrol(float)
//{
//    if (enemy->GetPlayer())
//        ChangeState(EnemyState::Alert);
//}
//
//void EnemyStateMachine::UpdateAlert(float)
//{
//    if (stateTimer > 0.5f)
//        ChangeState(EnemyState::Chase);
//}
//
//void EnemyStateMachine::UpdateChase(float)
//{
//    if (stateTimer > 5.0f)
//        ChangeState(EnemyState::Search);
//}
//
//void EnemyStateMachine::UpdateSearch(float)
//{
//    if (stateTimer > 3.0f)
//        ChangeState(EnemyState::Patrol);
//}
//
//void EnemyStateMachine::UpdateAttack(float)
//{
//    if (stateTimer > 0.8f)
//        ChangeState(EnemyState::Cooldown);
//}
//
//void EnemyStateMachine::UpdateCooldown(float)
//{
//    if (stateTimer > 1.0f)
//        ChangeState(EnemyState::Chase);
//}
//
//void EnemyStateMachine::UpdateHit(float)
//{
//    if (stateTimer > 0.3f)
//        ChangeState(EnemyState::Chase);
//}
//
//void EnemyStateMachine::UpdateReturn(float)
//{
//    if (stateTimer > 2.0f)
//        ChangeState(EnemyState::Patrol);
//}
