#include "Drawer2D.h"
#include "DirectX.h"
#include <vector>

void Drawer2D::DrawTexture(t_VertexPos v_, std::string fileName_)
{
	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;

	float width = v_.tex_pos_end.x - v_.tex_pos_start.x;
	float height = v_.tex_pos_end.y - v_.tex_pos_start.y;

	
	if (m_ptr_tex_list[fileName_] ) 
	{
		left_tu   = v_.tex_pos_start.x / m_ptr_tex_list[fileName_]->width;
		right_tu  = v_.tex_pos_end.x / m_ptr_tex_list[fileName_]->width;
		top_tv    = v_.tex_pos_start.y / m_ptr_tex_list[fileName_]->height;
		bottom_tv = v_.tex_pos_end.y / m_ptr_tex_list[fileName_]->height;
	}

#if 0
	// ���㌴�_�ɂ���ꍇ

	t_CustomVertex v[] =
	{
		{ v_.pos.x, v_.pos.y, 0.0f, 1.f,left_tu, top_tv},			// ����
		{ v_.pos.x + width, v_.pos.y, 0.0f, 1.f, right_tu, top_tv},			// �E��
		{ v_.pos.x + width, v_.pos.y + height, 0.0f, 1.f, right_tu, bottom_tv},			// �E��
		{ v_.pos.x, v_.pos.y + height, 0.0f, 1.f,left_tu, bottom_tv},			// ����
	};
#else
	// ���S�_�̍��W���w�肷��ꍇ

	float harf_x = 0.f;
	float harf_y = 0.f;
	if (m_ptr_tex_list[fileName_])
	{
		harf_x = width / 2.0f;
		harf_y = height / 2.0f;
	}

	// �O�p�`��`��
	t_CustomVertex v[] =
	{
		{ v_.pos.x - harf_x, v_.pos.y - harf_y, 0.0f, 1.f,left_tu, top_tv},			// ����
		{ v_.pos.x + harf_x, v_.pos.y - harf_y, 0.0f, 1.f,right_tu, top_tv},			// �E��
		{ v_.pos.x + harf_x, v_.pos.y + harf_y, 0.0f, 1.f,right_tu, bottom_tv},			// �E��
		{ v_.pos.x - harf_x, v_.pos.y + harf_y, 0.0f, 1.f,left_tu, bottom_tv},			// ����
	};
#endif

	// �@����ݒ肵�Ă��Ȃ���

	if (m_ptr_tex_list[fileName_]) {
		mgr->GetStatus()->d3d_device->SetTexture(0, m_ptr_tex_list[fileName_]->texture_data);
	}
	// ���C�e�B���O
	mgr->GetStatus()->d3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHW�Ŗ������_��LIGHT�������̂Ŗ����ɂ��Ă���

	mgr->GetStatus()->d3d_device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	mgr->GetStatus()->d3d_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(t_CustomVertex));
}

void Drawer2D::DrawTexture(Pos2 v_, std::string fileName_, int numX_, int numY_, int maxNumX_, int maxNumY_)
{
	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	float left_tu = 0.f;
	float right_tu = 1.f;
	float top_tv = 0.f;
	float bottom_tv = 1.f;

	float width = (m_ptr_tex_list[fileName_]->width / maxNumX_);
	float height = (m_ptr_tex_list[fileName_]->height / maxNumY_);

	float start_x = (m_ptr_tex_list[fileName_]->width / maxNumX_) * (numX_);
	float start_y = (m_ptr_tex_list[fileName_]->height / maxNumY_) * (numY_);
	float end_x = (m_ptr_tex_list[fileName_]->width / maxNumX_) * (numX_ + 1);
	float end_y = (m_ptr_tex_list[fileName_]->height / maxNumY_) * (numY_ + 1);


	if (m_ptr_tex_list[fileName_])
	{
		left_tu = start_x / m_ptr_tex_list[fileName_]->width;
		right_tu = end_x / m_ptr_tex_list[fileName_]->width;
		top_tv = start_y / m_ptr_tex_list[fileName_]->height;
		bottom_tv = end_y / m_ptr_tex_list[fileName_]->height;
	}

#if 1
	// ���㌴�_�ɂ���ꍇ

	t_CustomVertex v[] =
	{
		{ v_.x, v_.y, 0.0f, 1.f,left_tu, top_tv},			// ����
		{ v_.x + width, v_.y, 0.0f, 1.f, right_tu, top_tv},			// �E��
		{ v_.x + width, v_.y + height, 0.0f, 1.f, right_tu, bottom_tv},			// �E��
		{ v_.x, v_.y + height, 0.0f, 1.f,left_tu, bottom_tv},			// ����
	};
#else
	// ���S�_�̍��W���w�肷��ꍇ

	float harf_x = 0.f;
	float harf_y = 0.f;
	if (m_ptr_tex_list[fileName_])
	{
		harf_x = width / 2.0f;
		harf_y = height / 2.0f;
	}

	// �O�p�`��`��
	t_CustomVertex v[] =
	{
		{ v_.pos.x - harf_x, v_.pos.y - harf_y, 0.0f, 1.f,left_tu, top_tv},			// ����
		{ v_.pos.x + harf_x, v_.pos.y - harf_y, 0.0f, 1.f,right_tu, top_tv},			// �E��
		{ v_.pos.x + harf_x, v_.pos.y + harf_y, 0.0f, 1.f,right_tu, bottom_tv},			// �E��
		{ v_.pos.x - harf_x, v_.pos.y + harf_y, 0.0f, 1.f,left_tu, bottom_tv},			// ����
	};
#endif

	// �@����ݒ肵�Ă��Ȃ���

	if (m_ptr_tex_list[fileName_]) {
		mgr->GetStatus()->d3d_device->SetTexture(0, m_ptr_tex_list[fileName_]->texture_data);
	}
	// ���C�e�B���O
	mgr->GetStatus()->d3d_device->SetRenderState(D3DRS_LIGHTING, FALSE);	// RHW�Ŗ������_��LIGHT�������̂Ŗ����ɂ��Ă���

	mgr->GetStatus()->d3d_device->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);

	mgr->GetStatus()->d3d_device->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 2, v, sizeof(t_CustomVertex));
}


bool Drawer2D::CreateTexture(std::string fileName_)
{
	t_Size size;
	D3DXIMAGE_INFO info;

	m_ptr_tex_list[fileName_] = new t_Texture;

	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return false; }

	// 2�̗ݏ悶��Ȃ��P�[�X��z�肵�Č��̃T�C�Y���擾����D3DXCreateTextureFromFileEx�Ŏg��
	D3DXGetImageInfoFromFileA(fileName_.c_str(), &info);

	if (FAILED(D3DXCreateTextureFromFileExA(mgr->GetStatus()->d3d_device,
		fileName_.c_str(),
		info.Width,
		info.Height,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		0x0000ff00,
		nullptr,
		nullptr,
		&m_ptr_tex_list[fileName_]->texture_data)))
	{
		return false;
	}
	else
	{
		// �e�N�X�`���T�C�Y�̎擾
		D3DSURFACE_DESC desc;

		if (FAILED(m_ptr_tex_list[fileName_]->texture_data->GetLevelDesc(0, &desc)))
		{
			m_ptr_tex_list[fileName_]->texture_data->Release();
			return false;
		}
		// �f�J���|���S�����
		// �����ł͑z����̒l�������Ă���
		m_ptr_tex_list[fileName_]->width = (float)desc.Width;
		m_ptr_tex_list[fileName_]->height = (float)desc.Height;
	}

	return true;
}

void Drawer2D::DrawFont(t_Vec2 pos_,std::string text_) {

	DxManager* mgr = DxManager::GetInstance();
	if (!mgr) { return; }

	RECT rect =
	{
		(LONG)pos_.x,
		(LONG)pos_.y,
		(LONG)pos_.x + (LONG)1024.f,
		(LONG)pos_.y + (LONG)1024.f
	};

	LPD3DXFONT font = mgr->GetFont();

	font->DrawTextA(
		NULL,
		text_.c_str(),
		-1,
		&rect,
		DT_LEFT,
		D3DCOLOR_XRGB(255,255,255)
	);
}

void Drawer2D::Release(std::string fileName_) {

	m_ptr_tex_list[fileName_]->texture_data->Release();

	delete[] m_ptr_tex_list[fileName_];

	m_ptr_tex_list.clear();
}

void Drawer2D::AllRelease() {
	for (auto tex : m_ptr_tex_list) 
	{
		if (!tex.second) {
			delete tex.second;
			tex.second = nullptr;
		}
	}
}