///////////////////////////////////////////////////////////////////////////////
// songho.js
// =========
// Javascript module for www.songho.ca
//
//  AUTHOR: Song Ho Ahn (song.ahn@gmail.com)
// CREATED: 2012-11-09
// UPDATED: 2012-12-04
///////////////////////////////////////////////////////////////////////////////

// constants
var MARGIN_TOP_COMMENT = 15;
var SCROLL_DURATION = 600;  // ms

// register event handlers
addEvent(window, "load",   main,         false);
addEvent(window, "resize", handleResize, false);
addEvent(window, "scroll", handleScroll, false);



///////////////////////////////////////////////////////////////////////////////
// entry point when a page is loaded
///////////////////////////////////////////////////////////////////////////////
function main()
{
    // add click event to toogle comment block on/off
    var buttonComment = document.getElementById("buttonDisqus");
    if(buttonComment)
    {
        addEvent(buttonComment, "click", toogleCommentBlock, false);
    }
}



///////////////////////////////////////////////////////////////////////////////
// handle window resize event
///////////////////////////////////////////////////////////////////////////////
function handleResize(e)
{
    var commentBlock = document.getElementById("commentblock");
    if(commentBlock)
    {
        var windowHeight = getWindowHeight();
        var commentHeight = commentBlock.offsetHeight;
        if(windowHeight > commentHeight)
        {
            // reset the top position
            var offset = getScrollOffset();
            commentBlock.style.top = (offset.y + MARGIN_TOP_COMMENT) + "px";
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// handle window scroll event
///////////////////////////////////////////////////////////////////////////////
function handleScroll(e)
{
    var commentBlock = document.getElementById("commentblock");
    if(commentBlock)
    {
        if(!commentBlock.scrollTo)
            addScrollTo(commentBlock);

        var left = parseInt(commentBlock.style.left);

        //var contentHeight = document.getElementById("leftblock").offsetHeight;
        var windowHeight = getWindowHeight();
        var commentHeight = commentBlock.offsetHeight;
        if(windowHeight < commentHeight)
        {
            commentBlock.scrollTo(left, MARGIN_TOP_COMMENT, SCROLL_DURATION, AnimationMode.EASE_OUT);
        }
        else
        {
            var offset = getScrollOffset();
            //commentBlock.style.position = "absolute";
            commentBlock.scrollTo(left, MARGIN_TOP_COMMENT + offset.y, SCROLL_DURATION, AnimationMode.EASE_OUT);
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// toggle on/off comment bolck
///////////////////////////////////////////////////////////////////////////////
function toogleCommentBlock()
{
    var disqus = document.getElementById("disqus_thread");
    if(disqus)
    {
        // if visible, hide it
        if(disqus.style.display != "none")
        {
            disqus.style.display = "none";
            this.innerHTML = "Show Comments";
        }
        else
        {
            disqus.style.display = "block";
            this.innerHTML = "Hide Comments";
        }
    }
}



///////////////////////////////////////////////////////////////////////////////
// add an event handler, referenced from scottandrew.com
///////////////////////////////////////////////////////////////////////////////
function addEvent(element, type, listener, useCapture)
{
    if(element.addEventListener)
    {
        element.addEventListener(type, listener, useCapture);
        return true;
    }
    else if(element.attachEvent)
    {
        var result = element.attachEvent("on" + type, listener);
        return result;
    }
}



///////////////////////////////////////////////////////////////////////////////
// remove an event handler
///////////////////////////////////////////////////////////////////////////////
function removeEvent(element, type, listener, useCapture)
{
    if(element.removeEventListener)
    {
        element.removeEventListener(type, listener, useCapture);
        return true;
    }
    else if(element.attachEvent)
    {
        var result = element.detachEvent("on" + type, listener);
        return result;
    }
}



///////////////////////////////////////////////////////////////////////////////
// compute the client area of window (width and height)
///////////////////////////////////////////////////////////////////////////////
function getWindowWidth()
{
    return window.innerWidth || document.documentElement.clientWidth || document.body.clientWidth || 0;
}
function getWindowHeight()
{
    return window.innerHeight || document.documentElement.clientHeight || document.body.clientHeight || 0;
}



///////////////////////////////////////////////////////////////////////////////
// compute the offset position(left, top) of the element
///////////////////////////////////////////////////////////////////////////////
function getElementOffset(element)
{
    var x = 0;
    var y = 0;
    while(element)
    {
        x += element.offsetLeft || 0;
        y += element.offsetTop || 0;
        element = element.offsetParent; // next
    }
    return {x:x, y:y};
}



///////////////////////////////////////////////////////////////////////////////
// compute the scroll offset of the page
///////////////////////////////////////////////////////////////////////////////
function getScrollOffset()
{
    var x = window.pageXOffset || document.documentElement.scrollLeft;
    var y = window.pageYOffset || document.documentElement.scrollTop;
    return {x:x, y:y};
}



///////////////////////////////////////////////////////////////////////////////
// get requestAnimationFrame method for client browser
// If requestAnimationFrame() is implemented by the browser, use it to
// refresh the animations. Otherwise, use setTimeOut() with 16 ms interval.
///////////////////////////////////////////////////////////////////////////////
function getRequestAnimationFrameFunction(element)
{
    var names = ["requestAnimationFrame",
                 "mozRequestAnimationFrame",
                 "msRequestAnimationFrame",
                 "oRequestAnimationFrame",
                 "webkitRequestAnimationFrame"];
    var functionName = getAvailableFunctionFromList(element, names);
    if(functionName)
        return function(callback) { return element[functionName](callback); };
    else
        return function(callback) { return setTimeout(callback, 16); }; // 60 fps
}



///////////////////////////////////////////////////////////////////////////////
// get animationStartTime method for client browser
// Use "animationStartTime" property, if possible, to sync other animations.
///////////////////////////////////////////////////////////////////////////////
function getAnimationStartTimeFunction(element)
{
    var names = ["animationStartTime",
                 "mozAnimationStartTime",
                 "msAnimationStartTime",
                 "oAnimationStartTime",
                 "webkitAnimationStartTime"];
    var functionName = getAvailableFunctionFromList(element, names);
    if(functionName)
        return function(){ return element[functionName]; };
    else
        return function() { return Date.now(); };
}



///////////////////////////////////////////////////////////////////////////////
// find available function from given list
// if not, return null
///////////////////////////////////////////////////////////////////////////////
function getAvailableFunctionFromList(element, names)
{
    if(!element) return null;

    for(var i = 0, count = names.length; i < count; ++i)
    {
        var name = names[i];
        if(element[name])   // if function exists, return the function name as string
            return name;
    }
    return null;            // if not found, return null
}



///////////////////////////////////////////////////////////////////////////////
// animation mode and interpolation
///////////////////////////////////////////////////////////////////////////////
var AnimationMode = {
    LINEAR: 0,
    EASE_IN: 1,
    EASE_IN2: 2, // using circle
    EASE_OUT: 3,
    EASE_OUT2: 4, // using circle
    EASE_IN_OUT: 5,
    EASE_IN_OUT2: 6, // using circle
    BOUNCE: 7,
    ELASTIC: 8
};
function getInterpolateAlpha(alpha, mode)
{
    var HALF_PI = Math.PI * 0.5;
    var t = alpha;

    // recompute alpha based on animation mode
    if(mode == AnimationMode.EASE_IN)
    {
        t = 1 - Math.cos(HALF_PI * alpha);
    }
    else if(mode == AnimationMode.EASE_IN2)
    {
        t = 1 - Math.sqrt(1 - alpha * alpha);
    }
    else if(mode == AnimationMode.EASE_OUT)
    {
        t = Math.sin(HALF_PI * alpha);
    }
    else if(mode == AnimationMode.EASE_OUT2)
    {
        t = Math.sqrt(1 - (1 - alpha) * (1 - alpha));
    }
    else if(mode == AnimationMode.EASE_IN_OUT)
    {
        t = 0.5 * (1 - Math.cos(Math.PI * alpha));
    }
    else if(mode == AnimationMode.EASE_IN_OUT2)
    {
        if(alpha < 0.5)
            t = 0.5 * (1 - Math.sqrt(1 - alpha * alpha));
        else
            t = 0.5 * Math.sqrt(1 - (1 - alpha) * (1 - alpha)) + 0.5;
    }
    else if(mode == AnimationMode.BOUNCE)
    {
    }
    else if(mode == AnimationMode.ELASTIC)
    {
    }

    return t;
}



///////////////////////////////////////////////////////////////////////////////
// add scroll animation method to an element
///////////////////////////////////////////////////////////////////////////////
function addScrollTo(element)
{
    if(!element)
        return;

    element.scrollTo = function(left, top, duration, mode, callback)
    {
        callback = callback || function(){};
        var self = this;

        var from = {};
        from.left = parseInt(this.style.left);
        from.top = parseInt(this.style.top);
        from.time = Date.now();

        var to = {}
        to.left = left;
        to.top = top;
        to.time = from.time + duration;

        var requestAnimationFrame = getRequestAnimationFrameFunction(window);
        requestAnimationFrame(scrollToFrame);
        function scrollToFrame()
        {
            var time = Date.now();
            if(time >= to.time)
            {
                self.style.left = to.left + "px";
                self.style.top = to.top + "px";
                callback();
                return;
            }
            var alpha = (time - from.time) / duration;
            alpha = getInterpolateAlpha(alpha, mode); // adjust alpha based on anim mode

            var left = Math.round(from.left + (to.left - from.left) * alpha);
            var top = Math.round(from.top + (to.top - from.top) * alpha);
            self.style.left = left + "px";
            self.style.top = top + "px";
            requestAnimationFrame(scrollToFrame);
        }
    };
}
