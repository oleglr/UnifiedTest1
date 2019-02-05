#pragma once
// Copyright (c) .NET Foundation and contributors. All rights reserved. Licensed under the Microsoft Reciprocal License. See LICENSE.TXT file in the project root for full license information.


enum eAssemblyAttributes
{
    aaEventClass     = (1 << 0),
    aaDotNetAssembly = (1 << 1),
    aaPathFromGAC    = (1 << 2),
    aaRunInCommit    = (1 << 3)
};


// structs

struct CPISCHED_ROLE_ASSIGNMENT
{
    WCHAR wzKey[MAX_DARWIN_KEY + 1];

    INSTALLSTATE isInstalled, isAction;

    CPI_APPLICATION_ROLE* pApplicationRole;

    CPISCHED_ROLE_ASSIGNMENT* pNext;
};

struct CPISCHED_METHOD
{
    WCHAR wzKey[MAX_DARWIN_KEY + 1];
    WCHAR wzIndex[11 + 1];
    WCHAR wzName[MAX_DARWIN_COLUMN + 1];

    int iPropertyCount;
    CPI_PROPERTY* pProperties;

    int iRoleInstallCount;
    int iRoleUninstallCount;
    CPISCHED_ROLE_ASSIGNMENT* pRoles;

    CPISCHED_METHOD* pNext;
};

struct CPISCHED_INTERFACE
{
    WCHAR wzKey[MAX_DARWIN_KEY + 1];
    WCHAR wzIID[CPI_MAX_GUID + 1];

    int iPropertyCount;
    CPI_PROPERTY* pProperties;

    int iRoleInstallCount;
    int iRoleUninstallCount;
    CPISCHED_ROLE_ASSIGNMENT* pRoles;

    int iMethodCount;
    CPISCHED_METHOD* pMethods;

    CPISCHED_INTERFACE* pNext;
};

struct CPISCHED_COMPONENT
{
    WCHAR wzKey[MAX_DARWIN_KEY + 1];
    WCHAR wzCLSID[CPI_MAX_GUID + 1];

    int iPropertyCount;
    CPI_PROPERTY* pProperties;

    int iRoleInstallCount;
    int iRoleUninstallCount;
    CPISCHED_ROLE_ASSIGNMENT* pRoles;

    int iInterfaceCount;
    CPISCHED_INTERFACE* pInterfaces;

    ICatalogCollection* piSubsColl;

    CPISCHED_COMPONENT* pNext;
};

struct CPI_ASSEMBLY
{
    WCHAR wzKey[MAX_DARWIN_KEY + 1];
    WCHAR wzModule[MAX_DARWIN_KEY + 1];
    LPWSTR pwzAssemblyName;
    LPWSTR pwzDllPath;
    LPWSTR pwzTlbPath;
    LPWSTR pwzPSDllPath;
    int iAttributes;

    int iComponentCount;
    CPISCHED_COMPONENT* pComponents;

    BOOL fReferencedForInstall;
    BOOL fReferencedForUninstall;
    BOOL fIgnore;

    int iRoleAssignmentsInstallCount;
    int iRoleAssignmentsUninstallCount;

    INSTALLSTATE isInstalled, isAction;

    CPI_APPLICATION* pApplication;

    CPI_ASSEMBLY* pPrev;
    CPI_ASSEMBLY* pNext;
};

struct CPI_ASSEMBLY_LIST
{
    CPI_ASSEMBLY* pFirst;
    CPI_ASSEMBLY* pLast;

    int iInstallCount;
    int iCommitCount;
    int iUninstallCount;

    int iRoleInstallCount;
    int iRoleCommitCount;
    int iRoleUninstallCount;
};


// function prototypes

void CpiAssemblyListFree(
    CPI_ASSEMBLY_LIST* pList
    );
HRESULT CpiAssembliesRead(
    CPI_APPLICATION_LIST* pAppList,
    CPI_APPLICATION_ROLE_LIST* pAppRoleList,
    CPI_ASSEMBLY_LIST* pAsmList
    );
HRESULT CpiAssembliesVerifyInstall(
    CPI_ASSEMBLY_LIST* pList
    );
HRESULT CpiAssembliesVerifyUninstall(
    CPI_ASSEMBLY_LIST* pList
    );
HRESULT CpiAssembliesInstall(
    CPI_ASSEMBLY_LIST* pList,
    int iRunMode,
    LPWSTR* ppwzActionData,
    int* piProgress
    );
HRESULT CpiAssembliesUninstall(
    CPI_ASSEMBLY_LIST* pList,
    int iRunMode,
    LPWSTR* ppwzActionData,
    int* piProgress
    );
HRESULT CpiRoleAssignmentsInstall(
    CPI_ASSEMBLY_LIST* pList,
    int iRunMode,
    LPWSTR* ppwzActionData,
    int* piProgress
    );
HRESULT CpiRoleAssignmentsUninstall(
    CPI_ASSEMBLY_LIST* pList,
    int iRunMode,
    LPWSTR* ppwzActionData,
    int* piProgress
    );
HRESULT CpiGetSubscriptionsCollForComponent(
    CPI_ASSEMBLY* pAsm,
    CPISCHED_COMPONENT* pComp,
    ICatalogCollection** ppiSubsColl
    );
