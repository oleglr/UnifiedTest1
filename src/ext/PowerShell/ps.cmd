@setlocal
@pushd %~dp0

@set _C=Debug
:parse_args
@if /i "%1"=="release" set _C=Release& shift
@if not "%1"=="" shift & goto parse_args

@echo PowerShell.wixext build %_C%

:: Restore
msbuild -t:Restore -p:Configuration=%_C% || exit /b

:: Build
msbuild -t:Build -p:Configuration=%_C% test\WixToolsetTest.PowerShell\WixToolsetTest.PowerShell.csproj || exit /b

:: Test
dotnet test -c %_C% --no-build test\WixToolsetTest.PowerShell || exit /b

:: Pack
msbuild -t:Pack -p:Configuration=%_C% -p:NoBuild=true wixext\WixToolset.PowerShell.wixext.csproj || exit /b

@popd
@endlocal
