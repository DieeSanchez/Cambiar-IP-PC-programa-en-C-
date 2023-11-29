Option Explicit

Dim start_ip, end_ip, current_ip, free_ip
Dim i

start_ip = "192.168.11.40"
end_ip = "192.168.11.255"
free_ip = ""

For i = 1 To 255
    current_ip = Left(start_ip, Len(start_ip) - 1) & CStr(i)
    If Not Ping(current_ip) Then
        free_ip = current_ip
        Exit For
    End If
Next

If free_ip <> "" Then
    WScript.Echo free_ip
End If


Function Ping(ip)
    Dim objShell, objExec
    Dim pingCommand, pingResult

    Set objShell = CreateObject("WScript.Shell")
    pingCommand = "ping -n 1 " & ip
    Set objExec = objShell.Exec(pingCommand)
    pingResult = LCase(objExec.StdOut.ReadAll)
    
    If InStr(pingResult, "host de destino inaccesible") = 0 Then
        Ping = True
    Else
        Ping = False
    End If
End Function