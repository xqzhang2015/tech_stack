
<!-- MarkdownTOC -->

- [The Chart Template Developer’s Guide](#the-chart-template-developer%E2%80%99s-guide)
  - [CHARTS](#charts)
  - [helm create mychart](#helm-create-mychart)
  - [examples](#examples)
- [References](#references)

<!-- /MarkdownTOC -->

# The Chart Template Developer’s Guide

### CHARTS
As described in the Charts Guide, Helm charts are structured like this:

```
mychart/
  Chart.yaml
  values.yaml
  charts/
  templates/
  ...
```

### helm create mychart

```
$ helm create mychart
Creating mychart
```

mychart/templates/

* `NOTES.txt`: The _help text_ for your chart. This will be displayed to your users when they run `helm install`
* `deployment.yaml`: A basic manifest for creating a Kubernetes `deployment`
* `service.yaml`: A basic manifest for creating a `service endpoint` for your deployment
* `\_helpers.tpl`: A place to put template helpers that you can re-use throughout the chart


### examples

* Delete all helm releases

```sh
helm list | grep release-X | awk '{print $1}' | xargs helm delete --purge
```

* Cluster update: modify yaml, then

```sh
kops replace -f xxx.yml
kops update cluster $CLUSTER_NAME --yes # This change will apply to new instances only
kops rolling-update cluster --fail-on-validate-error="false" --force --yes

kops rolling-update cluster --fail-on-validate-error="false" --force --yes --instance-group aerospike-node-group-latest
kops rolling-update cluster --fail-on-validate-error="false" --force --yes --instance-group aerospike-node-group-prod
```

# References

`Root doc`
[docs.helm.sh: The Chart Template Developer’s Guide](https://docs.helm.sh/chart_template_guide)<br/>

[]()<br/>

[]()<br/>

[]()<br/>
