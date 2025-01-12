/*
	MK3SGL.h - Printer visualization for a MK3S, with MMU and print.

	Copyright 2020 VintagePC <https://github.com/vintagepc/>

 	This file is part of MK404.

	MK404 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MK404 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with MK404.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once

#include "../3rdParty/arcball/Camera.hpp"        // for Camera
//#include "GLHelper.h"
#include "GLObj.h"           // for GLObj
#include "GLPrint.h"         // for GLPrint
#include "../utility/IKeyClient.h"
#include "../utility/IScriptable.h"     // for IScriptable::LineStatus
#include "../utility/Scriptable.h"      // for Scriptable
#include <GL/glew.h>         // NOLINT for glTranslatef
#include <GL/freeglut_std.h> //
#include <atomic>            // for atomic, atomic_bool, atomic_int
#include <cstdint>          // for uint32_t
#include <string>            // for string
#include <vector>            // for vector

class HD44780GL;
class OBJCollection;
class Printer;

class MK3SGL: public Scriptable, private IKeyClient
{
    public:
        // Creates new MK3SGL object, with lite graphics (or full) and an MMU (or not)
        MK3SGL(const std::string &strModel, bool bMMU);

		~MK3SGL() override
		{
			g_pMK3SGL = nullptr;
		}

        // IRQ registration helper.
        void Init();

        // Draws the visuals within the current GL transformation context.
        void Draw();

        // Twists the displayed knob in response to input from mouse/keyboard.
        void TwistKnob(bool bDir);

        // Attaches the GL LCD for rendering.
        //void SetLCD(HD44780GL* pLCD){m_pLCD = pLCD;}

        // Clears the displayed print.
        void ClearPrint() { m_bClearPrints = true; }

        void ExportPLY() { m_bExportPLY = true; }

        // Resets the camera view to the starting position.
        void ResetCamera();

        // Toggles nozzle cam mode.
        void ToggleNozzleCam() {m_bFollowNozzle = !m_bFollowNozzle;}

        // Sets nozzle cam mode enabled to an explicit value.
        void SetFollowNozzle(bool bFollow) { m_bFollowNozzle = bFollow;}

		// Flags window for redisplay
		inline void FlagForRedraw() { glutPostWindowRedisplay(m_iWindow); }

        // IRQ receivers.
		void OnPosChanged(int source, float value);
		void OnMotorStep(int source, uint32_t value);
		void OnBoolChanged(int source, uint32_t value);

        // GL helpers needed for the window and mouse callbacks, use when creating the GL window.
        void MouseCB(int button, int state, int x, int y);
		void MotionCB(int x, int y);
        void SetWindow(int iWin) { m_iWindow = iWin;};
		void ResizeCB(int w, int h);

		inline void SetStepsPerMM(int16_t iX, int16_t iY, int16_t iZ, int16_t iE)
		{
			for (auto p: m_vPrints)
			{
				p->SetStepsPerMM(iX,iY,iZ,iE);
			}
		}

	protected:
		LineStatus ProcessAction(unsigned int iAct, const std::vector<std::string> &vArgs) override;


    private:

		void OnKeyPress(const Key& key) override;

		// Stuff needed for the mouse events to happen in the GL context.
		void ProcessAction_GL();
		std::atomic_int16_t m_iQueuedAct{-1};
		std::vector<std::string> m_vArgs;

        GLObj m_EVis {"assets/Triangles.obj"};
        GLObj m_MMUBase {"assets/MMU_stationary.obj"};
        GLObj m_MMUSel {"assets/MMU_Selector.obj"};
        GLObj m_MMUIdl {"assets/Idler_moving.obj"};

		//GLHelper m_snap{"3DView"};

		OBJCollection *m_Objs = nullptr;

		std::atomic_int m_iCurTool = {0};
        GLPrint m_Print = {0.8,0,0}, m_T1 = {0,0.8,0}, m_T2 = {0,0,0.8}, m_T3 = {0.8,0.4,0}, m_T4 = {0.8,0,0.8};

		std::vector<GLPrint*> m_vPrints = {&m_Print, &m_T1, &m_T2, &m_T3, &m_T4};

        Camera m_camera;

        std::vector<GLObj*> m_vObjMMU = {&m_EVis,&m_MMUBase, &m_MMUSel, &m_MMUIdl};

       // HD44780GL *m_pLCD = nullptr;

        std::atomic_bool m_bFollowNozzle = {false}; // Camera follows nozzle.
		std::atomic_bool m_bClearPrints = {false};
        std::atomic_bool m_bExportPLY = {false};
		// Export result. 0 = pending, 1 = failed, 2 = success.
		std::atomic_int m_iExportPLYResult {0};

		std::atomic<const std::string*> m_pExportFN {nullptr};

        // MMU draw subfunction.
        //void DrawMMU();

        // Draws a simple LED at a position.
        void DrawLED(float r, float g, float b);
		void DrawRoundLED();

        void OnMMULedsChanged(int source, uint32_t value);
		void OnToolChanged(int source, uint32_t iIdx);


        // Correction parameters to get the model at 0,0,0 and aligned with the simulated starting positions.
        std::atomic<float> m_fEPos = {0}, m_fXPos = {0.01}, m_fYPos = {0.01}, m_fZPos = {0.01}, m_fPPos = {0.f};

        float m_fSelCorr = 0.025f;
		std::atomic<float> m_fSelPos = {0.0f};

        // This is going to be in degrees rotation instead of mm
        float m_fIdlCorr = 120.00f;
		std::atomic<float> m_fIdlPos = {0.0f};

        std::atomic_int m_iKnobPos {0}, m_iFanPWM = {0}, m_iPFanPWM = {0}, m_iIdlPos = {0};

        // GL context only!!
        int m_iFanPos = 0, m_iPFanPos = 0;

        std::atomic_bool m_bDirty = {false},
			m_bMMU = {false},
			m_bBedOn = {false},
			m_bPINDAOn = {false},
			m_bFINDAOn = {false},
			m_bSDCard = {true},
			m_bPrintSurface = {true};

		uint64_t m_lastETick = 0;


        int m_iWindow = 0;

		// Useful for instant positioning.

		inline void DebugTx(){glTranslatef(m_flDbg,m_flDbg2,m_flDbg3);}

		std::atomic<float> m_flDbg = {0.0f}, m_flDbg2 = {0.0f}, m_flDbg3 = {0.0f};
		std::atomic_int m_iDbg = {0};

		enum Actions
		{
			ActClear,
			ActToggleNCam,
			ActResetView,
			ActMouse,
			ActMouseMove,
			ActNonLinearX,
			ActNonLinearY,
			ActNonLinearZ,
			ActNonLinearE,
            ActExportPLY,
			ActExportPLYFile
		};

		static MK3SGL *g_pMK3SGL;
		Printer *m_pParent = nullptr;

};
