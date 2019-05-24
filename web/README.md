# HTML DOM + JavaScript + Framework
<!-- MarkdownTOC -->

- [Knowledge](#knowledge)
  - [HTML DOM](#html-dom)
  - [JavaScript](#javascript)
  - [Bootstrap](#bootstrap)
  - [jQuery](#jquery)
  - [MVVM: react vs vue.js](#mvvm-react-vs-vuejs)
- [Usage](#usage)
  - [block ad](#block-ad)

<!-- /MarkdownTOC -->

# Knowledge
## HTML DOM
## JavaScript
## Bootstrap
## jQuery
## MVVM: react vs vue.js

# Usage

## block ad

```xml
<p class="inline-ad-slot" id="inline-ad-0" style="display:block;height:100px;margin-left:auto;margin-right:auto;width:728px;"> ... </p>
```
* only two lines. Maybe we could provide a customized Chrome extension to block ad.

```java
var myElements = document.querySelectorAll(".inline-ad-slot");
for (var i = 0; i < myElements.length; i++) { myElements[i].style.display = "none"; }
```

