#include "ASNET.Control.Text.h"



template<typename T>
void release(T &Interface) {
	if (Interface) Interface->Release();
	Interface = nullptr;
}

void ASNET::Control::Text::InitalizeCursorAnimation()
{
	CursorAnimation.SetType(ASNET::Control::AnimationType::Common);

	ASNET::Control::KeyFrame keyframe;
	keyframe.TextColor = ASNET::Graph::Color(D2D1::ColorF::Black, 1);
	keyframe.TimePos = 0;
	CursorAnimation.AddFrame(keyframe);

	keyframe.TextColor = ASNET::Graph::Color(D2D1::ColorF::Black, 0);
	keyframe.TimePos = 0.5f;
	CursorAnimation.AddFrame(keyframe);

	keyframe.TextColor = ASNET::Graph::Color(D2D1::ColorF::Black, 1);
	keyframe.TimePos = 1.f;
	CursorAnimation.AddFrame(keyframe);

	
}

void ASNET::Control::Text::UpdateText()
{
	release(g_text);
	ParentInterface.DeviceContextWrite->CreateTextLayout(&g_word[0],
		g_word.length(), *Fontface, g_size.width, g_size.height, &g_text);

}

void ASNET::Control::Text::UpdateColor()
{
	release(g_brush);
	ParentInterface.DeviceContext2D->CreateSolidColorBrush(g_color,
		&g_brush);
}

void ASNET::Control::Text::DrawCursor()
{
	if (CursorAnimation.End()) CursorAnimation.Start();
	ASNET::Graph::Point point = GetRealPosition(g_cursor_pos, g_cursor_direct);
	ParentGraph->DrawLine(D2D1::Point2F(point.x, point.y), D2D1::Point2F(point.x, point.y + GetHeight()),
		CursorAnimation.GetKeyFrame().TextColor, 0.7f);
	CursorAnimation.Pass(ParentGraph->RenderTime());
}

ASNET::Control::Text::Text(ASNET::Graph::Graph* graph, ASNET::Graph::Word word,
	ASNET::Graph::Size size, ASNET::Graph::Font * font, ASNET::Graph::Color color,
	ASNET::Graph::TextAlign horizontal, ASNET::Graph::TextAlign vertical)
{
	ParentGraph = graph;
	ParentInterface = graph->Interface();
	g_word = word;
	g_size = size;
	g_color = color;
	Fontface = font;

	Horizontal = horizontal;
	Vertical = vertical;

	g_cursor_pos = 0;
	g_cursor_direct = true;
	g_cursor_show = false;

	InitalizeCursorAnimation();

	UpdateColor();
	UpdateText();
}

void ASNET::Control::Text::SetWord(ASNET::Graph::Word word)
{
	g_word = word;
	UpdateText();
}

void ASNET::Control::Text::SetColor(ASNET::Graph::Color color)
{
	g_color = color;
	UpdateColor();
}

void ASNET::Control::Text::Insert(wchar_t buff)
{
	if (g_cursor_pos == 0 && g_cursor_direct == true) {
		g_word = buff + g_word;
		UpdateText();
		g_cursor_direct = false;
		return;
	}
	if (g_cursor_direct == true) {
		g_cursor_pos--;
		g_cursor_direct = false;
	}
	g_word.insert(g_word.begin() + g_cursor_pos + 1 , buff);
	g_cursor_pos++;
	UpdateText();
}

void ASNET::Control::Text::Delete()
{
	if (g_cursor_pos == 0 && g_cursor_direct == true) 
		return;
	if (g_cursor_direct == true) {
		g_cursor_pos--;
		g_cursor_direct = false;
	}
	g_word.erase(g_word.begin() + g_cursor_pos);
	g_cursor_direct = true;
	UpdateText();
}

auto ASNET::Control::Text::GetWord() -> ASNET::Graph::Word
{
	return g_word;
}

auto ASNET::Control::Text::GetColor() -> ASNET::Graph::Color
{
	return g_color;
}

auto ASNET::Control::Text::GetRealX(int textposition) -> float
{
	return GetRealPosition(textposition).x;
}

auto ASNET::Control::Text::GetRealY(int textposition) -> float
{
	return GetRealPosition(textposition).y;
}

auto ASNET::Control::Text::GetRealPosition(int textposition, bool isleft) -> ASNET::Graph::Point
{
	ASNET::Graph::Point point;
	DWRITE_HIT_TEST_METRICS hit;
	g_text->HitTestTextPosition(textposition, !isleft, &point.x, &point.y, &hit);
	return point;
}

auto ASNET::Control::Text::GetHeight() -> float
{
	DWRITE_TEXT_METRICS metrics;
	g_text->GetMetrics(&metrics);
	return metrics.height / (float)metrics.lineCount;
}

auto ASNET::Control::Text::GetTextPosition(ASNET::Graph::Point point) -> int
{
	DWRITE_HIT_TEST_METRICS hit;
	BOOL IsHead;
	BOOL IsInside;
	g_text->HitTestPoint(point.x, point.y, &IsHead, &IsInside, &hit);
	return hit.textPosition;
}

void ASNET::Control::Text::OnDraw(ASNET::Graph::Point origin)
{
	switch (Horizontal) {
	case ASNET::Graph::TextAlign::Center: {
		g_text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		break;
	}
	case ASNET::Graph::TextAlign::Left: {
		g_text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
		break;
	}
	case ASNET::Graph::TextAlign::Right: {
		g_text->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_TRAILING);
		break;
	}
	default:
		break;
	}
	switch (Vertical) {
	case ASNET::Graph::TextAlign::Center: {
		g_text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
		break;
	}
	case ASNET::Graph::TextAlign::Top: {
		g_text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_NEAR);
		break;
	}
	case ASNET::Graph::TextAlign::Bottom: {
		g_text->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_FAR);
		break;
	}
	default:
		break;
	}
	ParentInterface.DeviceContext2D->DrawTextLayout(origin, g_text, g_brush);
	if (g_cursor_show)
		DrawCursor();
}

void ASNET::Control::Text::CursorShow()
{
	g_cursor_show = true;
}

void ASNET::Control::Text::CursorHide()
{
	g_cursor_show = false;
}

void ASNET::Control::Text::CursorUp()
{
	ASNET::Graph::Point point = GetRealPosition(g_cursor_pos, g_cursor_direct);
	point.y -= GetHeight();
	SetCursorPosition(point);
}

void ASNET::Control::Text::CursorLeft()
{
	CursorAnimation.Stop();
	if (g_cursor_direct == false) { g_cursor_direct = true; return; }
	if (g_cursor_pos == 0) return;
	if (g_cursor_direct == true) {
		ASNET::Graph::Point now_pos = GetRealPosition(g_cursor_pos, g_cursor_direct);
		ASNET::Graph::Point tar_pos = GetRealPosition(g_cursor_pos - 1 , g_cursor_direct ^ true);
		if (now_pos.x != tar_pos.x || now_pos.y != tar_pos.y) { g_cursor_pos--; g_cursor_direct = false; }
		else g_cursor_pos--;
	}
}

void ASNET::Control::Text::CursorDown()
{
	ASNET::Graph::Point point = GetRealPosition(g_cursor_pos, g_cursor_direct);
	point.y += GetHeight();
	SetCursorPosition(point);
}

void ASNET::Control::Text::CuesorRight()
{
	CursorAnimation.Stop();
	if (g_cursor_direct == true) { g_cursor_direct = false; return; }
	if (g_cursor_pos == g_word.length() - 1) return;
	if (g_cursor_direct == false) {
		ASNET::Graph::Point now_pos = GetRealPosition(g_cursor_pos, g_cursor_direct);
		ASNET::Graph::Point tar_pos = GetRealPosition(g_cursor_pos + 1 , g_cursor_direct ^ true);
		if (now_pos.x != tar_pos.x || now_pos.y != tar_pos.y) { g_cursor_pos++; g_cursor_direct = true; }
		else g_cursor_pos++;
	}
}

void ASNET::Control::Text::SetCursorPosition(int textposition, bool IsLeft)
{
	CursorAnimation.Stop();
	g_cursor_pos = textposition;
	g_cursor_direct = IsLeft;
}

void ASNET::Control::Text::SetCursorPosition(ASNET::Graph::Point point)
{
	CursorAnimation.Stop();
	DWRITE_HIT_TEST_METRICS hit;
	BOOL IsHead;
	BOOL IsInside;
	g_text->HitTestPoint(point.x, point.y, &IsHead, &IsInside, &hit);
	if (IsInside == false) return;
	ASNET::Graph::Point tar_pos_left = GetRealPosition(hit.textPosition, true);
	ASNET::Graph::Point tar_pos_right = GetRealPosition(hit.textPosition, false);
	g_cursor_pos = hit.textPosition;
	if (Physics::Vector2::Distance(point.x, point.y, tar_pos_left.x, tar_pos_left.y) <
		Physics::Vector2::Distance(point.x, point.y, tar_pos_right.x, tar_pos_right.y))
		g_cursor_direct = true;
	else g_cursor_direct = false;
}

