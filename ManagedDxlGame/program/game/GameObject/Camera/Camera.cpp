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
    //�����̎������킩��Ȃ��������ߐ��l�Ń`�b�v�T�C�Y�ƃ`�b�v�̏c�~������
    const float maxX = MAXCHIP - halfWidth;
    const float maxY =  halfHeight;
    
    //clamp�֐��Ŕ͈͓��Ɏ��߂�Bclamp(�l, �ŏ��l, �ő�l)
    target_.x = std::clamp(target_.x, halfWidth, maxX);
    target_.y = std::clamp(target_.y, halfHeight, maxY);
}
void Camera::Scroll(const std::shared_ptr<Player>player)
{
    //�v���C���[�����ɔ����𒴂�����J�����̒ǐՂ��J�n�A����܂Ńv���C���[���W�ŕ`��
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
        //�J�����̒x��
        target_ += (player->GetPlayerPos() - target_) * 0.05f;
        //�Ō�܂ŗ�����J�����̒ǔ���~
        if (player->Getbattle()) {
            if (player->GetPlayerPos().x >= MAXSTAGE)
            {
                m_is_active_ = false;
            }
        }
    }
}

void Camera::CameRareset( const std::shared_ptr<Player>player) {
    //�J���������X�|�[���n��
    target_ = player->Getsavepos();
}