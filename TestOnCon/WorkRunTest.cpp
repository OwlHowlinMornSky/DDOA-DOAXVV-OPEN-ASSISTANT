/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
*
*     Copyright 2023-2024  Tyler Parret True
*
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
*
*        http://www.apache.org/licenses/LICENSE-2.0
*
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
*
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
#include "WorkRunTest.h"

#include <iostream>
#include <string>

#define CppConTest

#include "../CoreDll/IHelper.h"
#include "../CoreDll/Settings.h"

#include <Windows.h>

using namespace ohms;

void OutputLog() {
	std::cout << std::endl;
}

void OutputLog(std::string_view str) {
	std::cout << str << std::endl;
}

#define Log(expr) OutputLog(#expr)
#define LogStr(expr) (#expr)

int WorkRunTest() {
	auto r_helper = ohms::IHelper::instance();
	if (!r_helper) {
		return 1;
	}
	r_helper->setup(false);

	Settings::WndHandler::DEFAULT.Debug_ShowCapture = true;
	Settings::Global::DEFAULT.ClearList();
	Settings::Global::DEFAULT.Work_TaskList[0] = TaskEnum::LegacyCha;

	try {
		r_helper->start();

		while (true) {
			unsigned long m;
			while ((m = r_helper->msgPop()) != ReturnMsgEnum::None)
				switch (m) {
				case ReturnMsgEnum::CMD_EmptyLine:
					OutputLog();
					break;
				case ReturnMsgEnum::CMD_Stopped:
					Log(CMD_Stopped);
					//WorkUnlock();
					//timer_Main.Enabled = false;
					break;
				case ReturnMsgEnum::CMD_BtnToStop:
					Log(CMD_BtnToStop);
					//btn_Main.Text = Strings.Main.Btn_Main_Stop;
					//btn_Main.Enabled = true;
					//m_btnMainIsStart = false;
					break;
				case ReturnMsgEnum::CMD_BtnToStart:
					Log(CMD_BtnToStart);
					//btn_Main.Text = Strings.Main.Btn_Main_Start;
					//btn_Main.Enabled = true;
					//m_btnMainIsStart = true;
					break;

				case ReturnMsgEnum::LOG_StartError_Running:
					Log(Strings.LogEvent.Work_AlreadyRunning);
					break;
				case ReturnMsgEnum::LOG_Stopping:
					Log(Strings.LogEvent.Work_Stopping);
					break;
				case ReturnMsgEnum::LOG_Stopped:
					Log(Strings.LogEvent.Work_Stopped);
					break;
				case ReturnMsgEnum::LOG_Complete:
					Log(Strings.LogEvent.Work_Complete);
					/*if (Settings.GUI.Default.UseNotify)
						notifyIcon_Main.ShowBalloonTip(
							Settings.Param.Default.NotifyTime,
							Strings.LogEvent.Work_Complete,
							Strings.LogEvent.Work_Complete_Describtion,
							ToolTipIcon.Info
						);*/
					break;

				case ReturnMsgEnum::LOG_WorkError_ExceptionInternalError:
					OutputLog();
					Log(Strings.LogEvent.Work_Exception);
					/*if (Settings.GUI.Default.UseNotify)
						notifyIcon_Main.ShowBalloonTip(
							Settings.Param.Default.NotifyTime,
							Strings.LogEvent.Work_Error,
							Strings.LogEvent.Work_Exception,
							ToolTipIcon.Error
						);*/
					break;

				case ReturnMsgEnum::LOG_TaskStop:
					Log(Strings.LogEvent.Task_Stop);
					break;
				case ReturnMsgEnum::LOG_TaskComplete:
					Log(Strings.LogEvent.Task_Complete);
					break;
				case ReturnMsgEnum::LOG_TaskError_Exception:
					Log(Strings.LogEvent.Task_Exception);
					/*if (Settings.GUI.Default.UseNotify)
						notifyIcon_Main.ShowBalloonTip(
							Settings.Param.Default.NotifyTime,
							Strings.LogEvent.Work_Error,
							Strings.LogEvent.Task_Exception,
							ToolTipIcon.Error
						);*/
					break;
				case ReturnMsgEnum::LOG_TaskError:
				{
					m = r_helper->msgPop();
					std::string text;
					switch (m) {
					case ReturnMsgEnum::STR_Task_Challenge_NoNew:
						text = LogStr(Task_Challenge_NoNew);
						break;
					case ReturnMsgEnum::STR_Task_Challenge_NoLast:
						text = LogStr(Task_Challenge_NoLast);
						break;
					case ReturnMsgEnum::STR_Task_Challenge_NoEnter:
						text = LogStr(Task_Challenge_NoEnter);
						break;
					case ReturnMsgEnum::STR_Task_Challenge_NoStart:
						text = LogStr(Task_Challenge_NoStart);
						break;
					case ReturnMsgEnum::STR_Task_Challenge_TimeOut:
						text = LogStr(Task_Challenge_TimeOut);
						break;
					case ReturnMsgEnum::STR_Task_Challenge_NoEnd:
						text = LogStr(Task_Challenge_NoEnd);
						break;
					case ReturnMsgEnum::STR_Task_Challenge_NoOver:
						text = LogStr(Task_Challenge_NoOver);
						break;
					case ReturnMsgEnum::STR_Task_Challenge_AddNotSup:
						text = LogStr(Task_Challenge_AddNotSup);
						break;
					case ReturnMsgEnum::STR_Task_Challenge_IgnoreAddFailed:
						text = LogStr(Task_Challenge_IgnoreAddFailed);
						break;
					case ReturnMsgEnum::STR_Task_Challenge_OpenAddFailed:
						text = LogStr(Task_Challenge_OpenAddFailed);
						break;
					case ReturnMsgEnum::STR_Task_FailedToLoadTemplateFile:
						text = LogStr(Task_FailedToLoadTemplateFile);
						break;
					case ReturnMsgEnum::STR_Task_Error_NoWnd:
						text = LogStr(Task_CanNotFindWnd);
						break;
					case ReturnMsgEnum::STR_Task_Error_FailedCapture:
						text = LogStr(Task_CanNotCapture);
						break;
					default:
						text = LogStr(UNKNOWN);
						break;
					}
					//Log(Strings.LogEvent.Task_Error + ": " + text);
					std::cout << "Strings.LogEvent.Task_Error: " << text << std::endl;
					/*if (Settings.GUI.Default.UseNotify)
						notifyIcon_Main.ShowBalloonTip(
							Settings.Param.Default.NotifyTime,
							Strings.LogEvent.Task_Error,
							text,
							ToolTipIcon.Info
						);*/
					break;
				}

				case ReturnMsgEnum::LOG_Challenge_Start:
					Log(Strings.LogEvent.Challenge_Start);
					break;
				case ReturnMsgEnum::LOG_Challenge_BeginNum: // 挑战赛开始（下跟次数！）
					//Log(string.Format(Strings.LogEvent.Challenge_BeginNum, Program.helper.GetCode()));
					std::cout << "Strings.LogEvent.Challenge_BeginNum: " << r_helper->msgPop() << std::endl;
					break;
				case ReturnMsgEnum::LOG_Challenge_Over:
					Log(Strings.LogEvent.Challenge_Over);
					break;
				case ReturnMsgEnum::LOG_Challenge_Exit:
					Log(Strings.LogEvent.Challenge_Exit);
					break;
				//case ReturnMsgEnum::LOG_Challenge_EnterAdd:
				//	Log(Strings.LogEvent.Challenge_EnterAdd);
				//	break;
				case ReturnMsgEnum::LOG_Challenge_IgnoredAdd:
					Log(Strings.LogEvent.Challenge_IgnoredAdd);
					break;
				case ReturnMsgEnum::LOG_Challenge_NotFindAdd:
					Log(Strings.LogEvent.Challenge_NotFindAdd);
					break;
				case ReturnMsgEnum::LOG_Challenge_FindAdd:
					Log(Strings.LogEvent.Challenge_FindAdd);
					break;
				case ReturnMsgEnum::LOG_Challenge_OpenedAdd:
					Log(Strings.LogEvent.Challenge_OpenedAdd);
					break;
				default:
					Log(Strings.LogEvent.UNKNOWN);
					break;

				}
			Sleep(100);
		}
	}
	catch (...) {
		;
	}

	ohms::IHelper::drop();
	r_helper = nullptr;
	return 0;
}
