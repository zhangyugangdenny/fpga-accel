/*-
 *   BSD LICENSE
 *
 *   Copyright(c)  2019 Huawei Technologies Co., Ltd. All rights reserved.
 *
 *   Redistribution and use in source and binary forms, with or without
 *   modification, are permitted provided that the following conditions
 *   are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in
 *       the documentation and/or other materials provided with the
 *       distribution.
 *     * Neither the name of Huawei Technologies Co., Ltd  nor the names of its
 *       contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *   OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *   SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *   LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *   DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *   THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */


#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fmtkapi.h"

/*******************************************************************************
Function     : DemoSetProtectionStatus
Description  : Set the switch status
Input        : None
Output       : None
Return       : None
*******************************************************************************/
void DemoSetProtectionStatus()
{
    fmerrno Result = FM_API_ERR_CODE_EINVAL;
    FmSession* SessionHdl = NULL;
    unsigned Num = 0;
 
    Result  = FmAPI_Initialize(SELECTED_API_VERSION, SELECTED_API_SUB_VER);
    if (FM_API_SUCCESS != Result)
    {
        printf("Initialization failed.\n");
        return;
    }

    printf("FMTK api Initialized.\n");

    FmAPI_StartSession(&SessionHdl);
    
    Num = SessionHdl->PfNum;

    if ( 0 == Num )
    {
        printf("No fpga devices!\n");
        FmAPI_StopSession(SessionHdl);
        FmAPI_Unload();
        return;
    }
    else
    {
        printf("%u fpga devices founded!\n", Num);
    }

    printf("The demo will open the switch of slot 0\n");

    /* You can also use another slot to perform this operation */
    Result = FmAPI_SetOverPowerProtection(SessionHdl, 0, 0);

    if ( FM_API_ERR_NOT_SUPPORT == Result)
    {
        printf("FPGA:0 doesn't support this function.\n");
    }

    if ( FM_API_SUCCESS != Result )
    {
        printf("Failed to set the switch status of FPGA[0], err code: %d\n", Result);
    }
    else
    {
        printf("Succeeded in setting the switch status of FPGA[0].\n");
    }

    /* Other API call can be added here */
    
    /* stop sesssions; make sure all device mutex lock released */
    FmAPI_StopSession(SessionHdl);

    /* check sessions and release all resources */
    FmAPI_Unload();    
    
    return;    
}

/*******************************************************************************
Function     : main
Description  : Main function entry
Input        : None
Output       : None
Return       : 0:sucess other:fail
*******************************************************************************/
int main()
{
    DemoSetProtectionStatus();
    return 0;
}

