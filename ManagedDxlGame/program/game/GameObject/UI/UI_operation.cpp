#include "../dxlib_ext/dxlib_ext.h"
#include"UI_operation.h"

UIOperation::UIOperation()
{
	operation_gpc_hdl = LoadGraph("graphics/operation.png");
}

UIOperation::~UIOperation()
{
	DeleteGraph(operation_gpc_hdl);
}
void UIOperation::Draw() {
	DrawRotaGraph(DXE_WINDOW_WIDTH>>1, DXE_WINDOW_HEIGHT>>1, 1, 0, operation_gpc_hdl, true);
}