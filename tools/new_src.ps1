
function Show-Menu {
    param (
        [string] $Title = 'Creator'
    )
    $len = 40 - $Title.Length
    $l2 = $len / 2 
    $p1 = "".PadLeft($l2, [char]'=')
    $pad = "$p1 $Title $p1"
    $pad2 = "".PadLeft($pad.Length, [char]'=')
    Clear-Host
    Write-Host $pad2
    Write-Host $pad 
    Write-Host $pad2

    Write-Host "1) Create New File"
    Write-Host "2) Create File in Folder"
    Write-Host "0) Exit"
}

function New-Files {
    param (
        [string]$Folder = ''
    )
    $SRC_PATH = $(Split-Path $PSScriptRoot -Parent) + "/src"
    $f = Read-Host "New SRC file: "
    $fLower = $f.ToLower()
    $fUpper = $f.ToUpper()
    if ($Folder.Length -gt 0) {
        
        if ( -not (Test-Path -Path "$SRC_PATH/$Folder")) {
            New-Item -Path "$SRC_PATH" -Name $Folder -ItemType "directory" 
        }
        $Folder = "/$Folder"
    }
    $c = "$SRC_PATH$Folder/$fLower.c"
    $h = "$SRC_PATH$Folder/$fLower.h"

    New-Item -Path $c 
    New-Item -Path $h 

    $cContent = '#include "' + $fLower + '.h"'
    $hContent1 = "#ifndef SAGE_" + $fUpper + "_H"
    $hContent2 = "#define SAGE_" + $fUpper + "_H"
    $hContent3 = "// " + $fUpper
    $hContent4 = "#endif" 

    Add-Content -Path $c -Value $cContent

    Add-Content -Path $h -Value $hContent1
    Add-Content -Path $h -Value $hContent2
    Add-Content -Path $h -Value ""
    Add-Content -Path $h -Value ""
    Add-Content -Path $h -Value $hContent3
    Add-Content -Path $h -Value ""
    Add-Content -Path $h -Value ""
    Add-Content -Path $h -Value $hContent4
}

function New-File-2 {
    $f = Read-Host "Folder Name: "
    New-Files -Folder $f
}

do {
    Show-Menu -Title "File Creator"
    $sel = Read-Host ">"
    switch ($sel) {
        '1' { 
            New-Files 
        }
        '2' {
            New-File-2
        }
    } 
} until ($sel -eq '0')
