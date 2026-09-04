# Link this skill into %USERPROFILE%\.claude\skills so it's available in
# every project. Safe to re-run: if the link already points here, it's a
# no-op; if something else occupies the name, it asks before touching it.
#
# Uses a directory junction (New-Item -ItemType Junction) rather than a
# symbolic link because junctions don't require Administrator privileges or
# Developer Mode on Windows -- a plain symlink would fail for most users
# without one of those. Junctions work the same way here (the skill folder
# just appears at the target path); this only matters for anyone inspecting
# the link type directly.
#
# Usage (from PowerShell):
#   .\install.ps1

$ErrorActionPreference = "Stop"

$SkillSrc = (Resolve-Path (Join-Path $PSScriptRoot "..")).Path
$SkillName = Split-Path $SkillSrc -Leaf
$TargetDir = Join-Path $env:USERPROFILE ".claude\skills"
$Target = Join-Path $TargetDir $SkillName

New-Item -ItemType Directory -Force -Path $TargetDir | Out-Null

if (Test-Path $Target) {
    $item = Get-Item $Target -Force
    $isJunctionToHere = ($item.LinkType -eq "Junction") -and ($item.Target -eq $SkillSrc)

    if ($isJunctionToHere) {
        Write-Host "Already installed: $Target -> $SkillSrc"
        exit 0
    }

    Write-Host "Something already exists at $Target (and it's not a link to this skill)."
    Write-Host "Remove or rename it, then re-run this script."
    exit 1
}

New-Item -ItemType Junction -Path $Target -Target $SkillSrc | Out-Null
Write-Host "Installed: $Target -> $SkillSrc"
Write-Host "The skill is now available in every project. Candidate progress is stored"
Write-Host "separately at $env:USERPROFILE\.claude\coding-interview\candidate_profile.json, so"
Write-Host "reinstalling or updating this skill later won't touch your saved history."
