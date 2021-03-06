#include "NOT.h"
#include "../Utility/PrecisionChecker.h"
#include <fstream>
using std::ifstream;
using std::ofstream;


NOT::NOT( int r_FanOut):Gate(1,r_FanOut)
{
}

NOT::NOT(const GraphicsInfo &r_GfxInfo, int r_FanOut):Gate(1, r_FanOut)
{
	m_GfxInfo.x1 = r_GfxInfo.x1;
	m_GfxInfo.y1 = r_GfxInfo.y1;
	m_GfxInfo.x2 = r_GfxInfo.x2;
	m_GfxInfo.y2 = r_GfxInfo.y2;
}

void NOT::Save(ofstream& out)
{
	out << NOTType << '\t' ; 
	Gate::Save(out);
}

void NOT::Load(ifstream& in)
{
	Gate::Load(in);
}

void NOT::Operate()
{
	STATUS IN1=GetInputPinStatus(1);
	STATUS OUT1;
	
	OUT1 = (IN1 ? LOW : HIGH);
	
	m_OutputPin.setStatus(OUT1);
}


// Function Draw
// Draws 2-input NOT gate
void NOT::Draw(Output* pOut)
{
	pOut->DrawNOT(m_GfxInfo,selected,hoveredpin);
	DrawLabel(pOut);
}

void NOT::DrawWithDisplacement(Output* pOut,int deltaX,int deltaY)
{
	pOut->DrawNOT(m_GfxInfo,selected,hoveredpin,deltaX,deltaY);
}

InputPin* NOT::ReturnInputPinAT(int& x,int& y)
{

	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/2))
	{
		x=m_GfxInfo.x1;
		y=m_GfxInfo.y1+UI.GATE_Height/2;
		return &(this->m_InputPins[0]);
	}
	
	return NULL;
}

void NOT::getInputPinLocation(InputPin* p,int&x,int&y)
{
	x=m_GfxInfo.x1;
	y=m_GfxInfo.y1+UI.GATE_Height/2;
}

void NOT::HighlightPinsAT(int x,int y)
{
	hoveredpin=NO_PIN;

	HighlightOutPinsAT(x,y);
	
	if(WithinRange(x,m_GfxInfo.x1) && WithinRange(y,m_GfxInfo.y1+UI.GATE_Height/2))
		hoveredpin=INPUT1;

}

Component* NOT::CreateCopy()
{
	GraphicsInfo newl;
	newl.x1 = m_GfxInfo.x2+5;
	newl.y1 = m_GfxInfo.y2+5;
	newl.x2 = m_GfxInfo.x2+5+UI.GATE_Width;
	newl.y2 = m_GfxInfo.y2+5+UI.GATE_Height;
	NOT *n=new NOT(newl,NOT_FANOUT);
	n->selected=true;
	n->SetLabel(GetLabel());
	return n;
}
