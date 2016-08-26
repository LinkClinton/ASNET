#pragma once

#include"ASNET.Control.h"

#include<memory>

namespace ASNET {
	namespace Control {
		

		class Label:protected Control {
		protected:
			ASNET::Graph::Graph*     ParentGraph;
		public:
			float					 Left;
			float					 Right;
			float					 Top;
			float					 Bottom;

			wchar_t*                 Name;
			wchar_t*                 Text;

			ASNET::Control::Color    BackColor;
			ASNET::Control::Color    TextColor;

			ASNET::Graph::Font*      TextFont;

			ASNET::Graph::TextAlign  Horizontal;
			ASNET::Graph::TextAlign  Vertical;
		public:
			Label(ASNET::Graph::Graph* graph,
				float left, float right, float top, float bottom,
				wchar_t* name, wchar_t* text, wchar_t* fontface, float fontsize,
				ASNET::Graph::TextAlign horizontal = ASNET::Graph::TextAlign::Left,
				ASNET::Graph::TextAlign vertical = ASNET::Graph::TextAlign::Top);
			~Label();


			void reset(wchar_t* fontface, float fontsize);

			void Draw(ASNET::Graph::Graph* graph = nullptr);
		};


	}
}