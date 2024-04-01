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
#pragma once

namespace ohms::TaskExceptionCode {

constexpr int
UserStop = 0, // 用户主动停止，影响后续任务。
TaskComplete = 1, // 任务完成，不影响后续任务。
KnownErrorButNotCritical = 2, // 已知错误，但是不影响后续任务。
KnownErrorCritical = 3 // 已知错误，影响后续任务。
;

}
