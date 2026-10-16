$id = 'USB\ROOT_HUB30\5&29356010&0&0'
Write-Host "hub: $id"
Write-Host "state before: $((Get-PnpDevice -InstanceId $id).Status)"
Disable-PnpDevice -InstanceId $id -Confirm:$false
Start-Sleep -Seconds 2
Enable-PnpDevice -InstanceId $id -Confirm:$false
Start-Sleep -Seconds 3
Write-Host "state after: $((Get-PnpDevice -InstanceId $id).Status)"
Get-PnpDevice -PresentOnly | Where-Object { $_.InstanceId -like '*VID_2A0E*' } | ForEach-Object { Write-Host "M454: $($_.InstanceId) $($_.Status)" }
