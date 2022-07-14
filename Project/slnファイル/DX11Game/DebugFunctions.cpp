#include "DebugFunctions.h"

void DisplayFontList(D2D1_POINT_2F pos)
{
	D2DTextParams* texts[static_cast<int>(Font::Webdings) + 1];
	TextData td[static_cast<int>(Font::Webdings) + 1];
	for (auto&& s : texts) {
		s = new D2DTextParams();
	}

	float y = 0;
	int num = 0;
	for (auto&& d : td) {
		d.Str = "This is Japan.";
		d.Pos = { pos.x,pos.y + y };
		y -= 25;
		d.Form = TextData::FORM::Point;
		d.Data->fontSize = 20;
		d.Data->font = static_cast<Font>(num);
		num++;
	}
	for (int i = 0; i < static_cast<int>(Font::Webdings) + 1; i++) {
		texts[i]->SetData(&td[i]);
	}

	// delete����Ȃ��̂Ń��������[�N����B
	// �g�p����ӏ��ł͕K��D2DTextMng.AllRemove���ĂԂ���
}
