<!-- MarkdownTOC -->

- [The Bootstrap grid system](#the-bootstrap-grid-system)
- [...](#)

<!-- /MarkdownTOC -->

# The Bootstrap grid system

The Bootstrap grid system has four classes:

* __xs__ (for phones - screens less than 768px wide)
* __sm__ (for tablets - screens equal to or greater than 768px wide)
* __md__ (for small laptops - screens equal to or greater than 992px wide)
* __lg__ (for laptops and desktops - screens equal to or greater than 1200px wide)

Bootstrap's grid system allows up to 12 columns across the page. Note that numbers in __.col-*-*__ should always add up to 12 for each row.

* Example

```html
<div class="row">
  <div class="col-sm-4"></div>
  <div class="col-sm-8"></div>
</div>
<div class="row">
  <div class="col-*-*"></div>
  <div class="col-*-*"></div>
  <div class="col-*-*"></div>
</div>
```

# ...

