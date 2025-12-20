#include <ntddk.h>

// Driver Entry Point
NTSTATUS DriverEntry(_In_ PDRIVER_OBJECT DriverObject, _In_ PUNICODE_STRING RegistryPath) {
    UNREFERENCED_PARAMETER(RegistryPath);
    
    DriverObject->DriverUnload = NULL; // TODO: Implement Unload
    
    KdPrint(("AKIR: Driver Loaded\n"));
    
    // TODO: Register Process Notify Routine
    // PsSetCreateProcessNotifyRoutineEx(..., FALSE);
    
    return STATUS_SUCCESS;
}

