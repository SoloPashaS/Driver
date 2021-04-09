#pragma once
#include <fltKernel.h>
#include <dontuse.h>
#include <suppress.h>

/*************************************************************************
    Prototypes
*************************************************************************/

DRIVER_INITIALIZE DriverEntry;
NTSTATUS DriverEntry(
    _In_ PDRIVER_OBJECT DriverObject,
    _In_ PUNICODE_STRING RegistryPath
);

/*//////////////////////////////////////////////////////////////////////////////
    Callbacks start
*/

FLT_PREOP_CALLBACK_STATUS Create_Start(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _Flt_CompletionContext_Outptr_ PVOID* CompletionContext
);

FLT_POSTOP_CALLBACK_STATUS Create_Finish(
    _Inout_ PFLT_CALLBACK_DATA Data,
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_opt_ PVOID CompletionContext,
    _In_ FLT_POST_OPERATION_FLAGS Flags
);

/*
    Callbacks
*/

CONST FLT_OPERATION_REGISTRATION Callbacks[] = {
    { IRP_MJ_CREATE,
      0,
      Create_Start,
      Create_Finish 
    },
};

/*
    Callbacks fin
*//////////////////////////////////////////////////////////////////////////////

/*////////////////////////////////////////////////////////////////////////////
    Filter start
*/
NTSTATUS PtInstanceSetup(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ FLT_INSTANCE_SETUP_FLAGS Flags,
    _In_ DEVICE_TYPE VolumeDeviceType,
    _In_ FLT_FILESYSTEM_TYPE VolumeFilesystemType
);

NTSTATUS PtUnload(
    _In_ FLT_FILTER_UNLOAD_FLAGS Flags
);


/*
    Filter
*/
/*уникально идентифицирует мини фильтр и остается константой на все время работы драйвера.
Используется при активации или остановке процесса фильтрации.*/
PFLT_FILTER gFilterHandle;

CONST FLT_REGISTRATION FilterRegistration = {

    sizeof(FLT_REGISTRATION),         //  Size
    FLT_REGISTRATION_VERSION,           //  Version
    0,                                  //  Flags

    NULL,                               //  Context

    /*Callbacks – ссылка на структуру, определяющую, что и при помощи каких функций мы собираемся обрабатывать. */
    Callbacks,                          //  Operation callbacks

    PtUnload,                           //  MiniFilterUnload

    PtInstanceSetup,                    //  InstanceSetup
    
    NULL,                               //  InstanceQueryTeardown
    NULL,                               //  InstanceTeardownStart
    NULL,                               //  InstanceTeardownComplete

    NULL,                               //  GenerateFileName
    NULL,                               //  GenerateDestinationFileName
    NULL                                //  NormalizeNameComponent

};
/*
    Filter fin
*///////////////////////////////////////////////////////////////////////////////////////////////////////////


//MiniFilter callback routines sub_fun.????????????????????????????????????????????????????????
VOID PtOperationStatusCallback(
    _In_ PCFLT_RELATED_OBJECTS FltObjects,
    _In_ PFLT_IO_PARAMETER_BLOCK ParameterSnapshot,
    _In_ NTSTATUS OperationStatus,
    _In_ PVOID RequesterContext
);

BOOLEAN PtDoRequestOperationStatus(
    _In_ PFLT_CALLBACK_DATA Data
);




/*
    think about it
*/
ULONG_PTR OperationStatusCtx = 1;
ULONG gTraceFlags = 0;