# Remove the %USERPROFILE%\.claude\skills junction created by install.ps1.
# This does NOT delete your candidate_profile.json (your saved skill-level
# history) -- that lives in %USERPROFILE%\.claude\coding-interview\ and
# survives even if you uninstall or reinstall the skill itself. Pass
# -PurgeHistory to also delete it, if you really want to start over.
#
# Usage:
#   .\uninstall.ps1
#   .\uninstall.ps1 -PurgeHistory

param(
    [switch]$PurgeHistory
)

$ErrorActionPreference = "Stop"

$SkillSrc = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$SkillName = Split-Path $SkillSrc -Leaf
$Target = Join-Path $env:USERPROFILE ".claude\skills\$SkillName"
$ProfileDir = Join-Path $env:USERPROFILE ".claude\coding-interview"

if (Test-Path $Target) {
    $item = Get-Item $Target -Force
    if ($item.LinkType -eq "Junction") {
        Remove-Item $Target -Force
        Write-Host "Removed link: $Target"
    } else {
        Write-Host "$Target exists but isn't a link created by install.ps1; leaving it alone."
    }
} else {
    Write-Host "Nothing installed at $Target; nothing to do."
}

if ($PurgeHistory) {
    if (Test-Path $ProfileDir) {
        Remove-Item $ProfileDir -Recurse -Force
        Write-Host "Purged saved candidate history at $ProfileDir"
    } else {
        Write-Host "No saved history found at $ProfileDir"
    }
} else {
    Write-Host "Your candidate history (if any) is untouched at $ProfileDir"
}
