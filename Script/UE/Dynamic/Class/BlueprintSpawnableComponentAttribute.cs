using System;

namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Class)]
    public class BlueprintSpawnableComponentAttribute : UClassAttribute
    {
    public string MetaValue { get; set; }
    public BlueprintSpawnableComponentAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public BlueprintSpawnableComponentAttribute()
    {
    }
    }
}