# Translations

The sixbit-Core project has been designed to support multiple localisations. This makes adding new phrases, and completely new languages easily achievable. For managing all application translations, sixbit-Core uses the Transifex online translation management tool.

## Helping to translate (using Transifex)

Transifex monitors the GitHub repo for updates and processes new translation strings automatically after merges (may take several hours).

Multiple language support is critical for global adoption of sixbit. Contributions to translations are highly valuable.

## Writing code with translations

Translation files are located in:
`src/qt/locale/`

Naming format:
`sixbit_xx_YY.ts` or `sixbit_xx.ts`

`sixbit_en.ts` is the source template for all translations.

To regenerate:

```sh
cmake --preset dev-mode -DWITH_USDT=OFF -DENABLE_IPC=OFF
cmake --build build_dev_mode --target translate
```

Example:
```cpp
QToolBar *toolbar = addToolBar(tr("Tabs toolbar"));
```

## Pull Requests

Do NOT include translation updates in normal PRs.

```bash
git add src/qt/sixbitstrings.cpp src/qt/locale/sixbit_en.ts
git commit
```

## Transifex Setup

Signup:
https://app.transifex.com/signup/open-source/

CLI docs:
https://developers.transifex.com/docs/cli

Config file:
`.tx/config`

## Sync Translations

```bash
python3 ../sixbit-maintainer-tools/update-translations.py
git commit -a
```

Do not manually download translations.

## Handling Plurals

Steps:
1. Open `sixbit_en.ts` in Qt Linguist
2. Search for `%n`
3. Fill singular/plural fields
4. Mark complete
5. Save

## Adding New Language

Edit:
`src/qt/sixbit_locale.qrc`

Example:
```xml
<qresource prefix="/translations">
    <file alias="en">locale/sixbit_en.qm</file>
</qresource>
```

Note: must use `.qm` compiled files.

## Support

Translator mailing list:
https://groups.google.com/forum/#!forum/sixbit-translators
