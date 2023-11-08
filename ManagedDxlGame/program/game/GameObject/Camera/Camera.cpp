#include "../dxlib_ext/dxlib_ext.h"
#include"../game/Etc/Save.h"
#include"Camera.h"
#include"../Stage/Stage.h"
#include"../Player/Player.h"

Camera::Camera(const std::shared_ptr<SaveLoad>save){
    target_ = save->GetLoadCameraPos();
}
void Camera::DrawRange()
{
    const float halfWidth = DXE_WINDOW_WIDTH >> 1;
    const float halfHeight = DXE_WINDOW_HEIGHT >> 1;
    //引数の取り方がわからなかったため数値でチップサイズとチップの縦×横を代入
    const float maxX = MAXCHIP - halfWidth;
    const float maxY =  halfHeight;
    
    //clamp関数で範囲内に収める。clamp(値, 最小値, 最大値)
    target_.x = std::clamp(target_.x, halfWidth, maxX);
    target_.y = std::clamp(target_.y, halfHeight, maxY);
}
void Camera::Scroll(const std::shared_ptr<Player>player)
{
    //プレイヤーが横に半分を超えたらカメラの追跡を開始、それまでプレイヤー座標で描画
    if (!m_is_active_)
    {
        if (player->Getbattle()) {}
        else if (player->GetPlayerPos().x > DXE_WINDOW_WIDTH >> 1) {
            target_ = player->GetPlayerPos();
            m_is_active_ = true;
        }
    }
    else
    {
        //カメラの遅延
        target_ += (player->GetPlayerPos() - target_) * 0.05f;
        //最後まで来たらカメラの追尾停止
        if (player->Getbattle()) {
            if (player->GetPlayerPos().x >= MAXSTAGE)
            {
                m_is_active_ = false;
            }
        }
    }
}

void Camera::CameRareset( const std::shared_ptr<Player>player) {
    //カメラをリスポーン地へ
    target_ = player->Getsavepos();
}