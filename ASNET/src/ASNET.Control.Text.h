#pragma once

#include"ASNET.Control.h"

namespace ASNET {

	namespace Control {

	

		class Text {
		private:
			ASNET::Graph::Graph*    ParentGraph;
			ASNET::Graph::Interface ParentInterface;

			IDWriteTextLayout*    g_text;
			ID2D1SolidColorBrush* g_brush;

			ASNET::Graph::Word    g_word;
			ASNET::Graph::Size    g_size;
			ASNET::Graph::Color   g_color;

			int				      g_cursor_pos;
			bool                  g_cursor_show;
			bool				  g_cursor_direct;//true is left
		protected:
			void InitalizeCursorAnimation();

			ASNET::Control::Animation CursorAnimation;
		private:
			void UpdateText();
			void UpdateColor();
			void DrawCursor();
		public:
			Text(ASNET::Graph::Graph* graph, ASNET::Graph::Word word,
				ASNET::Graph::Size size, ASNET::Graph::Font* font,
				ASNET::Graph::Color color = D2D1::ColorF::Black,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);

			void SetWord(ASNET::Graph::Word word);

			void SetColor(ASNET::Graph::Color color);

			auto GetWord()->ASNET::Graph::Word;

			auto GetColor()->ASNET::Graph::Color;

			auto GetRealX(int textposition = 0)->float;
			auto GetRealY(int textposition = 0)->float;
			auto GetRealPosition(int textposition = 0, bool isleft = false)->ASNET::Graph::Point;

			auto GetHeight()->float;
			
			auto GetTextPosition(ASNET::Graph::Point point)->int;

			void OnDraw(ASNET::Graph::Point origin);

			ASNET::Graph::TextAlign Horizontal;
			ASNET::Graph::TextAlign Vertical;

			ASNET::Graph::Font*     Fontface;
			
			void CursorShow();
			void CursorHide();
			void CursorUp();
			void CursorLeft();
			void CursorDown();
			void CuesorRight();
			void SetCursorPosition(int textposition = 0 , bool IsLeft = false);
			void SetCursorPosition(ASNET::Graph::Point point);

		};

	}

}