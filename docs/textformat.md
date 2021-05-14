# Text File Format

The text documents are saved in a custom plain text file format with a structure based on how
open document text (.odt) files are saved. However, instead of using XML to describe the formatting
of the text, the formatting is instead encoded as plain text where each line corresponds to a
paragraph entry in the ODT XML.

This approach is also very compatible with how the QTextDocument class in Qt treats the text inside
the document. This makes it easy and fast to save and load text to and from the QTextDocument and
also later convert it to ODT.

Contrary to HTML, which sets formatting of text in overlapping regions which can have nested
formatting, Open Document, as well as the QTextDocument, describes the text in regions of equal
format, named fragments in Qt, meaning a new fragment start every time the format changes within a
paragraph.

## Paragraphs

The text file format consists of two parts. First is the paragraph format, or block format in Qt,
which is in ODT saved as a format reference for the each text paragraph, and in HTML would be
defined inside the `<p>` tag. In the Collett document format, these are saved as colon-separated
codes inside square brackets in front of the line.


### Block Type

| Code | Description               |
| ---- | ------------------------- |
| `H1` | Headers level 1 (Title)   |
| `H2` | Headers level 2 (Chapter) |
| `H3` | Headers level 3 (Scene)   |
| `H4` | Headers level 4 (Section) |
| `TX` | Regular text paragraph    |

### Block Alignment

| Code | Description   |
| ---- | ------------- |
| `AL` | Left aligned  |
| `AR` | Right aligned |
| `AC` | Centred       |
| `AJ` | Justified     |

## Fragments

Each fragment of the text within the paragraph is saved in a curly bracket open and close tag with
the codes `{f...}` and `{/f}`, similar to the text tags within paragraphs in ODT. The formatting
codes are saved within the opening tag after the initial `f`.


| Code | Description        |
| ---- | ------------------ |
| `b`  | Bold text          |
| `i`  | Italicised text    |
| `u`  | Underline text     |
| `s`  | Strikethrough text |

Since the curly bracket is used for in-text codes, actual curly brackets must be escaped. So is the
escape character itself.

| Code   | Description              |
| ------ | ------------------------ |
| `\lc\` | Left curly bracket, "{"  |
| `\rc\` | Right curly bracket, "}" |
| `\bs\` | Backslash, "\\"          |
