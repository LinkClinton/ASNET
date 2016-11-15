#include "ASNET.Control.Text.h"

template<typename T>
void release(T &Interface) {
	if (Interface) Interface->Release();
	Interface = nullptr;
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

auto ASNET::Control::Text::GetRealPosition(int textposition) -> ASNET::Graph::Point
{
	ASNET::Graph::Point point;
	DWRITE_HIT_TEST_METRICS hit;
	if (textposition >= 0)
		g_text->HitTestTextPosition(textposition, true, &point.x, &point.y, &hit);
	else
		g_text->HitTestTextPosition(0, false, &point.x, &point.y, &hit);
	return point;
}

auto ASNET::Control::Text::GetHeight() -> float
{
	DWRITE_TEXT_METRICS metrics;
	g_text->GetMetrics(&metrics);
	return metrics.height;
}

auto ASNET::Control::Text::GetTextPosition(ASNET::Graph::Point point) -> int
{
	DWRITE_HIT_TEST_METRICS hit;
	BOOL IsHead;
	BOOL IsIn;
	g_text->HitTestPoint(point.x, point.y, &IsHead, &IsIn, &hit);
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
}

