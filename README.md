SensibleEditorSourceCodeAccess
==============================

Clone this to your UnrealEngine directory at `Engine/Plugins/Developer`.

Add in Engine/Config/Linux/LinuxEngine.ini

```
[/Script/SourceCodeAccess.SourceCodeAccessSettings]
PreferredAccessor=SensibleEditorSourceCodeAccessor
```
and then in the head folder UnrealEngine:

```bash
make UE4Editor
```

Enable this as your code view editor.

You need to select a gui editor with `select-editor`.

### Funding

Accepting funding at: https://www.patreon.com/ernestlee
