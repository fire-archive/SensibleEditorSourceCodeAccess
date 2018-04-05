 /* Copyright (c) 2014 K. Ernest 'iFire' Lee

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  */

#include "SensibleEditorSourceCodeAccessor.h"
#include "SensibleEditorSourceCodeAccessPrivatePCH.h"
#include "DesktopPlatformModule.h"
#include <cstdlib>

#define LOCTEXT_NAMESPACE "SensibleEditorSourceCodeAccessor"

bool FSensibleSourceCodeAccessor::CanAccessSourceCode() const
{
  return FPaths::FileExists(TEXT("/usr/bin/clang"));
}

bool FSensibleSourceCodeAccessor::DoesSolutionExist() const
{ 
  FString SolutionPath;
  FDesktopPlatformModule::Get()->GetSolutionPath(SolutionPath);
  return FPaths::FileExists(SolutionPath);
} 

FName FSensibleSourceCodeAccessor::GetFName() const
{
  return FName("SensibleEditorSourceCodeAccessor");
}

FText FSensibleSourceCodeAccessor::GetNameText() const 
{
  return LOCTEXT("SensibleEditorDisplayName", "Sensible Editor");
}

FText FSensibleSourceCodeAccessor::GetDescriptionText() const
{
  return LOCTEXT("SensibleEditorDisplayDesc", "Open source code files with Sensible Editor");
}

bool FSensibleSourceCodeAccessor::OpenSolution()
{
  FString SolutionPath;
  if (FDesktopPlatformModule::Get()->GetSolutionPath(SolutionPath))
  {
    return OpenSolutionAtPath(SolutionPath);
  }
  return false;
}

bool FSensibleSourceCodeAccessor::OpenSolutionAtPath(const FString& InSolutionPath)
{
  FString FullPath = InSolutionPath;

  // Add this to handle spaces in path names.
  const FString NewFullPath = FString::Printf(TEXT("\"%s\""), *FullPath);

  FString Editor = FString(UTF8_TO_TCHAR(std::getenv("EDITOR")));
  if (Editor.IsEmpty())
  {
      Editor = FString(TEXT("/usr/bin/sensible-editor"));
  }

  if(FLinuxPlatformProcess::CreateProc(*Editor,
                                       *NewFullPath,
                                       true,
                                       true,
                                       false,
                                       nullptr,
                                       0,
                                       nullptr,
                                       nullptr).IsValid())
  {
    return true;
  }
  return false;
}

bool FSensibleSourceCodeAccessor::OpenFileAtLine(const FString& FullPath, int32 LineNumber, int32 ColumnNumber)
{
    FString Editor = FString(UTF8_TO_TCHAR(std::getenv("EDITOR")));
    if (Editor.IsEmpty())
    {
        Editor = FString(TEXT("/usr/bin/sensible-editor"));
    }

    // Add this to handle spaces in path names.
    const FString NewFullPath = FString::Printf(TEXT("\"%s+%d\""), *FullPath, LineNumber);

    if(FLinuxPlatformProcess::CreateProc(*Editor,
                                         *NewFullPath,
                                         true,
                                         true,
                                         false,
                                         nullptr,
                                         0,
                                         nullptr,
                                         nullptr).IsValid())
    {
      return true;
    }

  return false;
}

bool FSensibleSourceCodeAccessor::OpenSourceFiles(const TArray<FString>& AbsoluteSourcePaths) 
{
  for ( const FString& SourcePath : AbsoluteSourcePaths ) 
  {
    FString Editor = FString(UTF8_TO_TCHAR(std::getenv("EDITOR")));
    if (Editor.IsEmpty())
    {
        Editor = FString(TEXT("/usr/bin/sensible-editor"));
    }

    // Add this to handle spaces in path names.
    const FString NewSourcePath = FString::Printf(TEXT("\"%s\""), *SourcePath);

    if(!(FLinuxPlatformProcess::CreateProc(*Editor,
                                           *NewSourcePath,
                                           true,
                                           true,
                                           false,
                                           nullptr,
                                           0,
                                           nullptr,
                                           nullptr).IsValid()))
    {
        return false;
    }
  }  
  return true;
}

bool FSensibleSourceCodeAccessor::AddSourceFiles(const TArray<FString>& AbsoluteSourcePaths, const TArray<FString>& AvailableModules)
{
    return false;
}

bool FSensibleSourceCodeAccessor::SaveAllOpenDocuments() const
{
  return false;
}

void FSensibleSourceCodeAccessor::Tick(const float DeltaTime) 
{

}

#undef LOCTEXT_NAMESPACE
