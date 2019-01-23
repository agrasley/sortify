/* require css file for side effect only */
[@bs.val] external requireCSS: string => unit = "require";

let flip = (f, a, b) => f(b,a);